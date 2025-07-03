#include"chara_base.h"
#include "../ui/ui_manager.h"
#include <cassert>
#include "../game_mode/log_manager.h"
#include "../defs/state_defs.h"




CharaBase::CharaBase(const std::string& NAME, const int MAX_HP, const int ATTACK, const int DEFENSE, const character::CharaType CHARA_TYPE)
	: NAME_(NAME)
	, MAX_HP_(MAX_HP)
	, attack_(ATTACK)
	, defense_(DEFENSE)
	, CHARA_TYPE_(CHARA_TYPE)
{}

CharaBase::~CharaBase()
{
}

void CharaBase::Initialize()
{
	hp_ = MAX_HP_;
	abnormal_states_info_.clear();
}


int CharaBase::SufferAttack(const int OPPONENT_ATTACK, const std::string& OPPONENT_NAME)
{
	// ダメージの計算
	const int DAMAGE = CalcDamage(OPPONENT_ATTACK, defense_);
	CalcHp(DAMAGE);
	ui::DispBattleInfo(DAMAGE, OPPONENT_NAME, NAME_, hp_);
	return DAMAGE;
}

void CharaBase::TurnEndProcess()
{
	// 防御力を元に戻す
	if (behavior_ == BehaviorPattern::DEFENSE)
	{
		defense_ /= character::DEFENSE_MAGNIFICATION;
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
		abnormal_states_info_.clear();
	}
	else
	{
		// 状態の中に普通があった場合は消す
		const auto it = abnormal_states_info_.find(character::State::NORMAL);
		if (it != abnormal_states_info_.end())
		{
			abnormal_states_info_.erase(it);
		}
		// 影響を受ける回数をセット
		abnormal_states_info_[STATE] = StateMap::GetStateMap()->GetTurnNum(STATE);

	}
	ui::DispNewState(STATE, NAME_);
}

//	状態を反映させる(自分が攻撃を受ける側の時に毎回反映させる)
void CharaBase::ReflectState()
{
	for (auto it = abnormal_states_info_.begin(); it != abnormal_states_info_.end();)
	{
		int damage{};
		// 死んでいたら終了
		if (IsDead())
		{
			break;
		}
		if (it->first == character::State::NORMAL)
		{
			// 状態異常ない場合は探索終了
			break;
		}

		// 状態異常効果を反映
		const auto EFFECT_FUNC = state_map::GetStateEffectFunc(it->first);
		EFFECT_FUNC(*this, damage);

		// 状態異常を反映した結果をUIに出す
		ui::DispReflectState(it->first, NAME_, damage, hp_);

		// 状態異常の寿命処理
		if (--it->second == 0)
		{
			it = abnormal_states_info_.erase(it);
		}
		else
		{
			++it;
		}
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
		const int DAMAGE = target->SufferAttack(attack_, NAME_);
		log.damage = DAMAGE;
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
	if (hp_ < 0)
	{
		hp_ = 0;
	}
}

const int CharaBase::CalcDamage(const int ATTACK, const int DEFENSE)
{
	return std::max(0, ATTACK * ATTACK_MULTIPLIER - DEFENSE);
}


