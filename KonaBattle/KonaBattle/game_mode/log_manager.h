#pragma once
#include "../character/chara_base.h"
#include <string>
#include <vector>

struct ActionLog
{
    std::string attacker_name{};         // 行動したキャラ名
    std::string target_name{};        // 対象キャラ名（省略可）
    BehaviorPattern behavior{}; // 行動の種類（攻撃、防御など）
    int damage{};                 // 与えたダメージ（攻撃の場合）
    std::vector<character::State> added_state{}; // 状態異常（毒など）
    ActionLog(std::string attacker_name, std::string target_name, const BehaviorPattern BEHAVIOR)
        :attacker_name(std::move(attacker_name))
        , target_name(std::move(target_name))
        , behavior(BEHAVIOR) {}
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
    void ShowRecentLog(const int NUM) const;

private:
    // コンストラクタの隠蔽
    LogManager() {};
    LogManager(const LogManager& obj) = delete;
    // 行動を文字に直す
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

