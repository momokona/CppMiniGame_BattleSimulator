#include <string>
#include <string_view>
#pragma once
constexpr std::string_view PLAYER_NAME = "�R�i";

// �s���p�^�[��
enum class BehaviorPattern
{
	INVALID = 0,	// �����l
	ATTACK,	// �U��
	DEFENSE,	// �h��
	ITEM,		// �A�C�e��
	POISON,		// �ōU��(�G�̂�)
};