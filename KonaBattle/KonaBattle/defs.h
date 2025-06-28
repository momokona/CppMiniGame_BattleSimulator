#include <string>
#include <string_view>
#pragma once
constexpr std::string_view PLAYER_NAME = "コナ";

// 行動パターン
enum class BehaviorPattern
{
	INVALID = 0,	// 無効値
	ATTACK,	// 攻撃
	DEFENSE,	// 防御
	ITEM,		// アイテム
	POISON,		// 毒攻撃(敵のみ)
};