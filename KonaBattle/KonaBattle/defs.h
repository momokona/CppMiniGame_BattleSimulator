#include <string>
#include <string_view>
#pragma once
constexpr std::string_view PLAYER_NAME = "�R�i";
constexpr int PLAYER_MAX_HP = 100;
constexpr int PLAYER_INIT_ATTACK = 100;
constexpr int PLAYER_INIT_DEFENSE = 100;

constexpr std::string_view ENEMY1_NAME = "�i�K��";
constexpr int ENEMY1_MAX_HP = 80;
constexpr int ENEMY1_INIT_ATTACK = 120;
constexpr int ENEMY1_INIT_DEFENSE = 80;

// �s���p�^�[��
enum class BehaviorPattern
{
	INVALID = 0,	// �����l
	ATTACK,	// �U��
	DEFENSE,	// �h��
	ITEM,		// �A�C�e��
	POISON,		// �ōU��(�G�̂�)
};