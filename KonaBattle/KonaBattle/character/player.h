#pragma once
#include"chara_base.h"
class Player :public CharaBase
{
public:
	Player(const std::string NAME, const int MAX_HP, const int ATTACK, const int DEFENSE)
		:CharaBase(NAME, MAX_HP, ATTACK, DEFENSE, character::CharaType::PLAYER) {
	}
	~Player() {}
	// プレイヤーの選択によって決まる
	void SetBehevior(const BehaviorPattern behavior)
	{
		behavior_ = behavior;
	}
	const BehaviorPattern GetNextBehavior() override
	{
		return behavior_;
	}
private:
	// 一つしかクラスを作りたくないためコピーコンストラクタは禁止
	Player(const Player&)
		:CharaBase(NAME_, 0, 0, 0, character::CharaType::PLAYER) {};
};