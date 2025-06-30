#include "enemy.h"
void Enemy::DecideAction()
{
	// HP�����Ȃ��Ƃ��͖h��D��
	if (hp_ < MAX_HP_ / 2)
	{
		action_queue_.push({ BehaviorPattern::DEFENSE, 100 });
		action_queue_.push({ BehaviorPattern::ATTACK, 99 });
	}
	else
	{
		action_queue_.push({ BehaviorPattern::ATTACK, 1 });
		action_queue_.push({ BehaviorPattern::POISON, 2 });
	}
}

const BehaviorPattern Enemy::GetNextBehavior()
{
	// ���ɃZ�b�g�ς݂������炻�̒l��Ԃ�
	if (behavior_ != BehaviorPattern::INVALID)
	{
		return behavior_;
	}
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
