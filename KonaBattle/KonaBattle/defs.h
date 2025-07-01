#pragma once
#include <string>
#include <string_view>
constexpr std::string_view PLAYER_NAME = "�R�i";
constexpr int PLAYER_MAX_HP = 100;
constexpr int PLAYER_INIT_ATTACK = 12;
constexpr int PLAYER_INIT_DEFENSE = 5;

constexpr std::string_view ENEMY1_NAME = "�i�K��";
constexpr int ENEMY1_MAX_HP = 70;
constexpr int ENEMY1_INIT_ATTACK = 8;
constexpr int ENEMY1_INIT_DEFENSE = 3;

constexpr int ATTACK_MULTIPLIER = 2;

// �s���p�^�[��
enum class BehaviorPattern
{
	INVALID = 0,	// �����l
	ATTACK,	// �U��
	DEFENSE,	// �h��
	ITEM,		// �A�C�e��
	POISON,		// �ōU��(�G�̂�)
};