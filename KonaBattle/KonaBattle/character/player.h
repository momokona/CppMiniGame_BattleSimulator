#pragma once
#include"chara_base.h"
class Player :public CharaBase
{
public:
	Player(const std::string& NAME, const int MAX_HP, const int ATTACK, const int DEFENSE)
		:CharaBase(NAME, MAX_HP, ATTACK, DEFENSE, character::CharaType::PLAYER) {
	}
	~Player() {}
	// �v���C���[�̑I���ɂ���Č��܂�
	void Setbehavior(const BehaviorPattern behavior)
	{
		behavior_ = behavior;
	}
	BehaviorPattern GetNextBehavior() override
	{
		return behavior_;
	}
private:
	// ������N���X����肽���Ȃ����߃R�s�[�R���X�g���N�^�͋֎~
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
};