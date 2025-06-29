#include <string>
#include <string_view>
#pragma once
constexpr std::string_view PLAYER_NAME = "コナ";
constexpr int PLAYER_MAX_HP = 100;
constexpr int PLAYER_INIT_ATTACK = 100;
constexpr int PLAYER_INIT_DEFENSE = 100;

constexpr std::string_view ENEMY1_NAME = "ナガワ";
constexpr int ENEMY1_MAX_HP = 80;
constexpr int ENEMY1_INIT_ATTACK = 120;
constexpr int ENEMY1_INIT_DEFENSE = 80;

// 行動パターン
enum class BehaviorPattern
{
	INVALID = 0,	// 無効値
	ATTACK,	// 攻撃
	DEFENSE,	// 防御
	ITEM,		// アイテム
	POISON,		// 毒攻撃(敵のみ)
};