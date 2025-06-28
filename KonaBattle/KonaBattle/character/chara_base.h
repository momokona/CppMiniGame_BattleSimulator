#pragma once
#include <string>
#include <set>
#include <vector>
#include"../defs.h"

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
	CharaBase(const std::string NAME, const int MAX_HP, const int ATTACK, const int DEFENSE, const character::CharaType CHARA_TYPE = character::CharaType::ENEMY);
	virtual ~CharaBase() = 0;
	virtual void Initialize();
	void SufferAttack(const int OPPONENT_ATTACK, const std::string OPPONENT_NAME);
	void SetState(character::State state);
	void ReflectState();	// ��Ԃ𔽉f������
	const bool IsDead()
	{
		return hp_ <= 0;
	}
	void Act(CharaBase& target);
protected:
	void CalcHp(const int DAMAGE);
	virtual const BehaviorPattern GetBehavior()
	{
		return BehaviorPattern::INVALID;	// �p����Ŏ���
	}
protected:
	std::set<character::State> states_{};	// ���
	const std::string NAME_{};	// ���O
	const character::CharaType CHARA_TYPE_{ character::CharaType::ENEMY };
	const int MAX_HP_{};	// �ő�̗�
	int hp_{};	// �̗�
	int attack_{};	// �U����
	int defense_{};	// �h���

};