#include "enemy.h"
#include <random>
void Enemy::DecideAction()
{
	static std::random_device rd;	// ランダムな数を一つ作る道具(シード)
	static std::mt19937 gen(rd());	// 乱数を次々に作る機械、シードがないと動かない

	std::uniform_int_distribution<> dist(0, 99);	// genから生成された乱数を0～99の範囲に整える

	action_queue_.push({ BehaviorPattern::ATTACK, dist(gen) });
	action_queue_.push({ BehaviorPattern::DEFENSE, dist(gen) });
	action_queue_.push({ BehaviorPattern::POISON, dist(gen) });
}

BehaviorPattern Enemy::GetNextBehavior()
{
	// 既にセット済みだったらその値を返す
	if (behavior_ != BehaviorPattern::INVALID)
	{
		return behavior_;
	}
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
