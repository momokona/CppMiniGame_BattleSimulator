#pragma once
#include "../character/chara_base.h"
#include <string>
#include <vector>

struct ActionLog
{
    const std::string ATTACKER_NAME{};         // 行動したキャラ名
    const std::string TARGET_NAME{};        // 対象キャラ名（省略可）
    const BehaviorPattern BEHAVIOR{}; // 行動の種類（攻撃、防御など）
    int damage{};                 // 与えたダメージ（攻撃の場合）
    std::vector<character::State> added_state{}; // 状態異常（毒など）
    ActionLog(std::string attacker_name, std::string target_name, const BehaviorPattern BEHAVIOR)
        :ATTACKER_NAME(std::move(attacker_name))
        , TARGET_NAME(std::move(target_name))
        , BEHAVIOR(BEHAVIOR) {}
};

class LogManager
{
public:
    static void Create();
    static void Destroy()
    {
        delete log_manager_;
    }
    void AddLog(const ActionLog& LOG)
    {
        behavior_log_.push_back(LOG);
    }
    void ShowLog() const;
    static LogManager* GetLogManager()
    {
        return log_manager_;
    }
    void ShowRecentLog(const int NUM);

private:
    // コンストラクタの隠蔽
    LogManager() {};
    LogManager(const LogManager& obj) {};
    // 行動を文字に直す
    const std::string BehaviorToString(const BehaviorPattern PATTERN) const;
    const std::string StateToString(const character::State STATE) const;
    void ShowOneLog(const ActionLog& log) const;
private:
    std::vector<ActionLog> behavior_log_{};	// 行動履歴
    static LogManager* log_manager_;
};

namespace action_log
{
void AddLog(const ActionLog& LOG);
void ShowLog();
void ShowRecentLog(const int NUM);

}   // namespace action_log

