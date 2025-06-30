#pragma once
#include <string>
#include <vector>
#include "../character/chara_base.h"
namespace game_mode
{
	

}	// namespace game_mode


struct ActionLog
{
    const std::string ATTACKER_NAME{};         // 行動したキャラ名
    const std::string TARGET_NAME{};        // 対象キャラ名（省略可）
    const BehaviorPattern BEHAVIOR{}; // 行動の種類（攻撃、防御など）
    int damage{};                 // 与えたダメージ（攻撃の場合）
    std::vector<character::State> added_state{}; // 状態異常（毒など）
    ActionLog(const std::string ATTACKER_NAME, const std::string TARGET_NAME, const BehaviorPattern BEHAVIOR)
        :ATTACKER_NAME(ATTACKER_NAME)
        , TARGET_NAME(TARGET_NAME)
        , BEHAVIOR(BEHAVIOR) {}
};

class LogManager
{
public:
    void AddLog(const ActionLog& LOG)
    {
        behavior_log_.push_back(LOG);
    }
    void ShowLog() const;
    static LogManager* GetLogManager()
    {
        return log_manager_;
    }
private:
    // コンストラクタの隠蔽
    LogManager() {};
    LogManager(const LogManager& obj) {};
    // 行動を文字に直す
    std::string BehaviorToString(BehaviorPattern pattern);
private:
    std::vector<ActionLog> behavior_log_{};	// 行動履歴
    static LogManager* log_manager_{};
};

namespace log
{
void AddLog(const ActionLog& LOG);

}