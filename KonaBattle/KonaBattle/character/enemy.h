#pragma once
#include"chara_base.h"
#include <queue>

namespace enemy
{
struct Action
{
	BehaviorPattern behavior_{ BehaviorPattern::INVALID};
	int priority{};
	const bool operator<(const Action& other) const
	{
		return priority < other.priority;
	}
};
}	// namespace enemy
class Enemy : public CharaBase
{
public:
	Enemy(const std::string& NAME, const int MAX_HP, const int ATTACK, const int DEFENSE)
		:CharaBase(NAME, MAX_HP, ATTACK, DEFENSE, character::CharaType::ENEMY) {
	}
	~Enemy() {}

	void DecideAction();
	BehaviorPattern GetNextBehavior() override;

private:
	std::priority_queue<enemy::Action> action_queue_{};	// 優先順位がついてる行動パターン

};