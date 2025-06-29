#include "enemy.h"
void Enemy::DecideAction()
{
	// HPが少ないときは防御優先
	if (hp_ < MAX_HP_ / 4)
	{
		action_queue_.push({ BehaviorPattern::DEFENSE, 1 });
	}
	else
	{
		action_queue_.push({ BehaviorPattern::ATTACK, 1 });
		action_queue_.push({ BehaviorPattern::ITEM, 2 });
	}
}

const BehaviorPattern Enemy::GetNextBehavior()
{
	if (action_queue_.empty())
	{
		// 行動が決まってなかったら決める
		DecideAction();
	}
	// キューからアクションを取り出して削除
	const enemy::Action action = action_queue_.top();
	action_queue_.pop();
	behavior_ = action.behavior_;
	return behavior_;
}
