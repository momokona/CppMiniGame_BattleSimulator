#pragma once
#include <string>
#include <vector>
#include "../character/chara_base.h"
namespace game_mode
{
	

}	// namespace game_mode

// 行動パターン(ログ用)
enum class BehaviorPattern
{
	ATTACK = 0,	// 攻撃
	DEFENSE,	// 防御
	ITEM,		// アイテム
};
struct ActionLog
{
    const std::string ACtOR_NAME;         // 行動したキャラ名
    const BehaviorPattern BEHAVIOR; // 行動の種類（攻撃、防御など）
    const std::string TARGET_NAME;        // 対象キャラ名（省略可）
    const int DAMAGE{};                 // 与えたダメージ（攻撃の場合）
    std::vector<character::State> ADDED_STATES{}; // 状態異常（毒など）

};

class BattleLogManager
{
public:
    void AddLog(ActionLog& log)
    {
        behavior_log_.push_back(log);
    }
    void ShowLog();
private:
    // コンストラクタの隠蔽
    BattleLogManager() {};
    BattleLogManager(const BattleLogManager& obj) {};
    // 行動を文字に直す
    std::string BehaviorToString(BehaviorPattern pattern);
private:
    std::vector<ActionLog> behavior_log_{};	// 行動履歴
};