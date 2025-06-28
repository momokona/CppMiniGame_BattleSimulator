#pragma once
#include"chara_base.h"
#include <queue>

namespace enemy
{
struct Action
{
	BehaviorPattern behavior_{ BehaviorPattern::INVALID};
	int priority{};
	bool operator<(const Action& other)
	{
		return priority < other.priority;
	}
};
}	// namespace enemy
class Enemy : public CharaBase
{
public:
	Enemy(const std::string NAME, const int MAX_HP, const int ATTACK, const int DEFENSE, const character::CharaType CHARA_TYPE = character::CharaType::ENEMY)
		:CharaBase(NAME, MAX_HP, ATTACK, DEFENSE, CHARA_TYPE) {
	}
	~Enemy() {}

	void DecideAction();
private:
	const BehaviorPattern GetBehavior() override;
private:
	std::priority_queue<enemy::Action> action_queue_{};	// 優先順位がついてる行動パターン

};