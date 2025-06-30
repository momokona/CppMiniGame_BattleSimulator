#pragma once
#include <string>
#include <set>
#include <vector>
#include"../defs.h"
#include <memory>

// �O���Q��
struct ActionLog;

namespace character
{
	// ���
	enum class State
	{
		NORMAL = 0,			// �ʏ���
		POISON,			// �ŏ��
		NUM,
	};

	// �L�����N�^�[�̎��
	enum class CharaType
	{
		PLAYER = 0,		// ��l��
		ENEMY,		// �G
	};

	constexpr int DEFENSE_MAGNIFICATION = 2;	// �h���I�񂾎��̖h�䗦
}	// namespace character

// �L�����N�^�[��Base�N���X
class CharaBase
{
public:
	CharaBase(const std::string NAME, const int MAX_HP, const int ATTACK, const int DEFENSE, const character::CharaType CHARA_TYPE);
	virtual ~CharaBase() = 0;
	virtual void Initialize();
	void SufferAttack(const int OPPONENT_ATTACK, const std::string OPPONENT_NAME, ActionLog& log);
	void SetState(const character::State STATE);
	void ReflectState();	// ��Ԃ𔽉f������
	const bool IsDead()
	{
		return hp_ <= 0;
	}
	void Act(std::shared_ptr<CharaBase> target);

	void TurnEndProcess();
	virtual const BehaviorPattern GetNextBehavior()
	{
		return BehaviorPattern::INVALID;	// �p����Ŏ���
	}

	void DefenseProcess();

	const std::string& GetName() const
	{
		return NAME_;
	}
protected:
	void CalcHp(const int DAMAGE);
	const int CalcDamage(const int ATTACK, const int DEFENSE);

protected:
	std::set<character::State> states_{};	// ���
	const std::string NAME_{};	// ���O
	const character::CharaType CHARA_TYPE_{ character::CharaType::ENEMY };
	const int MAX_HP_{};	// �ő�̗�
	int hp_{};	// �̗�
	int attack_{};	// �U����
	int defense_{};	// �h���
	int poison_state_num_{};	// �ŏ�ԂɂȂ����^�[��

	BehaviorPattern behavior_{ BehaviorPattern::INVALID };


};