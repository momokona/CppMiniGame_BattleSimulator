#pragma once
#include <string>
#include <set>
#include <vector>
#include"../defs.h"

namespace character
{
	// 状態
	enum class State
	{
		NORMAL = 0,			// 通常状態
		POISON,			// 毒状態
		NUM,
	};

	// キャラクターの種類
	enum class CharaType
	{
		PLAYER = 0,		// 主人公
		ENEMY,		// 敵
	};

	constexpr int DEFENSE_MAGNIFICATION = 2;	// 防御を選んだ時の防御率
}	// namespace character

// キャラクターのBaseクラス
class CharaBase
{
public:
	CharaBase(const std::string NAME, const int MAX_HP, const int ATTACK, const int DEFENSE, const character::CharaType CHARA_TYPE = character::CharaType::ENEMY);
	virtual ~CharaBase() = 0;
	virtual void Initialize();
	void SufferAttack(const int OPPONENT_ATTACK, const std::string OPPONENT_NAME);
	void SetState(character::State state);
	void ReflectState();	// 状態を反映させる
	const bool IsDead()
	{
		return hp_ <= 0;
	}
	void Act(CharaBase& target);
protected:
	void CalcHp(const int DAMAGE);
	virtual const BehaviorPattern GetBehavior()
	{
		return BehaviorPattern::INVALID;	// 継承先で実装
	}
protected:
	std::set<character::State> states_{};	// 状態
	const std::string NAME_{};	// 名前
	const character::CharaType CHARA_TYPE_{ character::CharaType::ENEMY };
	const int MAX_HP_{};	// 最大体力
	int hp_{};	// 体力
	int attack_{};	// 攻撃力
	int defense_{};	// 防御力

};