#include"chara_base.h"
#include "../ui/ui_manager.h"
#include <cassert>
#include "../game_mode/log_manager.h"

constexpr int POISON_DAMAGE = 10;
constexpr int POISON_NUM = 3;

CharaBase::CharaBase(const std::string& NAME, const int MAX_HP, const int ATTACK, const int DEFENSE, const character::CharaType CHARA_TYPE)
	: NAME_(NAME)
	, MAX_HP_(MAX_HP)
	, attack_(ATTACK)
	, defense_(DEFENSE)
	, CHARA_TYPE_(CHARA_TYPE)
{
	Initialize();
}

CharaBase::~CharaBase()
{
}

void CharaBase::Initialize()
{
	hp_ = MAX_HP_;
	states_.clear();
}


void CharaBase::SufferAttack(const int OPPONENT_ATTACK, const std::string& OPPONENT_NAME, ActionLog& log)
{
	// ダメージの計算
	const int DAMAGE = CalcDamage(OPPONENT_ATTACK, defense_);
	CalcHp(DAMAGE);
	log.damage = DAMAGE;
	ui::DispBattleInfo(DAMAGE, OPPONENT_NAME, NAME_, hp_);
}

void CharaBase::TurnEndProcess()
{
	// 防御力を元に戻す
	if (behavior_ == BehaviorPattern::DEFENSE)
	{
		defense_ /= character::DEFENSE_MAGNIFICATION;
	}

	// 状態異常・毒の処理
	for(auto abnormal_state_info : abnormal_states_info_)
	{
		if (--abnormal_state_info.second == 0)
		{
			states_.erase(character::State::POISON);
		}
	}
	behavior_ = BehaviorPattern::INVALID;
}


void CharaBase::DefenseProcess()
{
	defense_ *= character::DEFENSE_MAGNIFICATION;
	ui::DispBehavior(BehaviorPattern::DEFENSE, NAME_);
}

void CharaBase::SetState(const character::State STATE)
{
	// NORMAL状態にセットされたら全ての状態異常を打ち消す
	if(STATE == character::State::NORMAL)
	{
		states_.clear();
	}
	else
	{
		// 状態の中に普通があった場合は消す
		const auto it = states_.find(character::State::NORMAL);
		if (it != states_.end())
		{
			states_.erase(it);
		}
		// 毒の回数をセット
		if (STATE == character::State::POISON)
		{
			abnormal_states_info_[character::State::POISON] = POISON_NUM;
		}
	}
	states_.insert(STATE);
	ui::DispNewState(STATE, NAME_);
}

//	状態を反映させる(自分が攻撃を受ける側の時に毎回反映させる)
void CharaBase::ReflectState()
{
	for (const auto state : states_)
	{
		int damage{};
		// 死んでいたら終了
		if (IsDead())
		{
			break;
		}
		if (state == character::State::NORMAL)
		{
			// 状態異常ない場合は探索終了
			break;
		}
		else if (state == character::State::POISON)
		{
			// 毒状態の時はダメージを受ける
			damage = POISON_DAMAGE;
			CalcHp(damage);
		}
		// 状態異常を反映した結果をUIに出す
		ui::DispReflectState(character::State::POISON, NAME_, damage, hp_);
	}
}
// 防御したとき以外の処理
void CharaBase::Act(std::shared_ptr<CharaBase> target)
{
	if (!target)
	{
		assert(false);
		printf("攻撃される側のデータがありません\n");
		return;
	}
	const BehaviorPattern BEHAVIOR = GetNextBehavior();
	ActionLog log{ NAME_, target->GetName(), BEHAVIOR };
	if (BEHAVIOR == BehaviorPattern::DEFENSE)
	{
		action_log::AddLog(log);
		return;
	}

	ui::DispBehavior(GetNextBehavior(), NAME_);

	if (BEHAVIOR == BehaviorPattern::ATTACK)
	{
		target->SufferAttack(attack_, NAME_, log);
	}
	else if(BEHAVIOR == BehaviorPattern::ITEM)
	{
		// アイテムを使った時の処理を書く.アイテムは未実装なので毒にしている。
		log.added_state.push_back(character::State::POISON);
		target->SetState(character::State::POISON);

	}
	else if (BEHAVIOR == BehaviorPattern::POISON)
	{
		if (CHARA_TYPE_ == character::CharaType::PLAYER)
		{
			// 毒攻撃を使えるのは敵だけ
			assert(false);
			printf("ui_managerがありません\n");
			return;
		}
		log.added_state.push_back(character::State::POISON);
		target->SetState(character::State::POISON);
	}
	action_log::AddLog(log);
}

void CharaBase::CalcHp(const int DAMAGE)
{
	hp_ -= DAMAGE;
	if (IsDead())
	{
		hp_ = 0;
	}
}

const int CharaBase::CalcDamage(const int ATTACK, const int DEFENSE)
{
	return std::max(0, ATTACK * ATTACK_MULTIPLIER - DEFENSE);
}
