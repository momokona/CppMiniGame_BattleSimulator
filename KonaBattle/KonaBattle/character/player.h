#pragma once
#include"chara_base.h"
class Player :public CharaBase
{
public:
	Player(const std::string NAME, const int MAX_HP, const int ATTACK, const int DEFENSE, const character::CharaType CHARA_TYPE = character::CharaType::ENEMY)
		:CharaBase(NAME, MAX_HP, ATTACK, DEFENSE, CHARA_TYPE) {
	}
	~Player() {}
	// プレイヤーの選択によって決まる
	void SetBehevior(const BehaviorPattern behavior)
	{
		behavior_ = behavior;
	}
private:
	const BehaviorPattern GetBehavior() override
	{
		return behavior_;
	}
private:
	BehaviorPattern behavior_{ BehaviorPattern::INVALID };
};