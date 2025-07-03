#pragma once
#include <string>
#include <set>
#include <vector>
#include"../defs/defs.h"
#include <memory>
#include <unordered_map>

// 前方参照
struct ActionLog;
class CharaBase;

constexpr int POISON_DAMAGE = 10;
constexpr int POISON_NUM = 2;

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
	CharaBase(const std::string& NAME, const int MAX_HP, const int ATTACK, const int DEFENSE, const character::CharaType CHARA_TYPE);
	virtual ~CharaBase() = 0;
	virtual void Initialize();
	int SufferAttack(const int OPPONENT_ATTACK, const std::string& OPPONENT_NAME);
	void SetState(const character::State STATE);
	void ReflectState();	// 状態を反映させる
	const bool IsDead()
	{
		return hp_ <= 0;
	}
	void Act(std::shared_ptr<CharaBase> target);

	void TurnEndProcess();
	virtual BehaviorPattern GetNextBehavior()
	{
		return BehaviorPattern::INVALID;	// 継承先で実装
	}

	void DefenseProcess();

	const std::string& GetName() const
	{
		return NAME_;
	}
	void CalcHp(const int DAMAGE);
	character::CharaType GetCharaType()
	{
		return CHARA_TYPE_;
	}

protected:
	const int CalcDamage(const int ATTACK, const int DEFENSE);

protected:
	std::unordered_map<character::State, int> abnormal_states_info_{};	// 状態異常になったターン
	const std::string NAME_{};	// 名前
	const character::CharaType CHARA_TYPE_{ character::CharaType::ENEMY };
	const int MAX_HP_{};	// 最大体力
	int hp_{};	// 体力
	int attack_{};	// 攻撃力
	int defense_{};	// 防御力

	BehaviorPattern behavior_{ BehaviorPattern::INVALID };
};


