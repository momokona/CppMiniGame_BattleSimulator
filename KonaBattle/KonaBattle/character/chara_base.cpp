#include"chara_base.h"

constexpr int POISON_DAMAGE = 10;

CharaBase::CharaBase(const std::string NAME, const int MAX_HP, const int ATTACK, const int DEFENSE, const character::CharaType CHARA_TYPE)
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

void CharaBase::SufferAttack(const int OPPONENT_ATTACK, const std::string OPPONENT_NAME)
{
	// ダメージの計算
	const int DAMAGE = OPPONENT_ATTACK - defense_;
	printf("%sは%sに%dのダメージを与えた！\n", OPPONENT_NAME, NAME_, DAMAGE);
	CalcHp(DAMAGE);
}

void CharaBase::SetState(character::State state)
{
	// NORMAL状態にセットされたら全ての状態異常を打ち消す
	if(state == character::State::NORMAL)
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
	}
	states_.insert(state);
}

//	状態を反映させる
void CharaBase::ReflectState()
{
	for (const auto state : states_)
	{
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
			CalcHp(POISON_DAMAGE);
		}
	}
}

void CharaBase::CalcHp(const int DAMAGE)
{
	hp_ -= DAMAGE;
	if (IsDead())
	{
		hp_ = 0;
	}
	printf("%sの残りのHPは%dになった。\n", NAME_, hp_);
	if (IsDead())
	{
		printf("%sの負け！\n", NAME_, hp_);
	}
}