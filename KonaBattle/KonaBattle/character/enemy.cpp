#include "enemy.h"
void Enemy::DecideAction()
{
	// HP�����Ȃ��Ƃ��͖h��D��
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
		// �s�������܂��ĂȂ������猈�߂�
		DecideAction();
	}
	// �L���[����A�N�V���������o���č폜
	const enemy::Action action = action_queue_.top();
	action_queue_.pop();
	behavior_ = action.behavior_;
	return behavior_;
}
