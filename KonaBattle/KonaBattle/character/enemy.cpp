#include "enemy.h"
#include <random>
void Enemy::DecideAction()
{
	static std::random_device rd;	// �����_���Ȑ������铹��(�V�[�h)
	static std::mt19937 gen(rd());	// ���������X�ɍ��@�B�A�V�[�h���Ȃ��Ɠ����Ȃ�

	std::uniform_int_distribution<> dist(0, 99);	// gen���琶�����ꂽ������0�`99�͈̔͂ɐ�����

	action_queue_.push({ BehaviorPattern::ATTACK, dist(gen) });
	action_queue_.push({ BehaviorPattern::DEFENSE, dist(gen) });
	action_queue_.push({ BehaviorPattern::POISON, dist(gen) });
}

BehaviorPattern Enemy::GetNextBehavior()
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
