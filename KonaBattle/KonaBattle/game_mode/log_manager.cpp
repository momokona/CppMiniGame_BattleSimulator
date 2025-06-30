#include "log_manager.h"
#include <iostream>
#include"../defs.h"
#include <cassert>
#include <unordered_map>
LogManager* LogManager::log_manager_ = nullptr;

void LogManager::Create()
{
    if (log_manager_)
    {
        return;
    }
    log_manager_ = new LogManager;
}


void LogManager::ShowLog() const
{
    printf("\n\n");
    printf("**戦歴まとめ**\n");
    printf("\n");
    for (const auto& log : behavior_log_)
	{
		// TODO:ログの出力をする
        const std::string BEHAVIIOR = BehaviorToString(log.BEHAVIOR);
        std::string state{};
        for (const auto add_state : log.added_state)
        {
            if (state != "")
            {
                state += ", ";
            }
            state += StateToString(add_state);
        }

        printf("攻撃者:%s\n", log.ATTACKER_NAME.c_str());
        printf("ターゲット:%s\n", log.TARGET_NAME.c_str());
        printf("行動:%s\n", BEHAVIIOR.c_str());
        if (!log.added_state.empty())
        {
            printf("与えた状態異常：%s\n", state.c_str());
        }
        if (log.BEHAVIOR == BehaviorPattern::ATTACK || log.damage > 0)
        {
            printf("与えたダメージ：%d\n", log.damage);
        }
        printf("\n");
	}
}

const std::string& LogManager::BehaviorToString(const BehaviorPattern PATTERN) const
{
    static const std::unordered_map<BehaviorPattern, std::string> BEHAVIOR_NAME_MAP =
    {
        {BehaviorPattern::ATTACK, "攻撃"},
        {BehaviorPattern::DEFENSE, "防御"},
        {BehaviorPattern::ITEM, "アイテム"},
        {BehaviorPattern::POISON, "毒攻撃"},
    };
    const auto it = BEHAVIOR_NAME_MAP.find(PATTERN);
    if (it != BEHAVIOR_NAME_MAP.end())
    {
        return it->second;
    }
    return "不明";
}

const std::string& LogManager::StateToString(const character::State STATE) const
{
    static const std::unordered_map<character::State, std::string> STATE_NAME_MAP =
    {
        {character::State::NORMAL, "通常"},
        {character::State::POISON, "毒"},
    };
    const auto it = STATE_NAME_MAP.find(STATE);
    if (it != STATE_NAME_MAP.end())
    {
        return it->second;
    }
    return "不明";
}


namespace action_log
{
void AddLog(const ActionLog& LOG)
{
    const auto log_manager = LogManager::GetLogManager();
    if (!log_manager)
    {
        assert(false);
        printf("log_managerがありません\n");
        return;
    }
    log_manager->AddLog(LOG);
}

void ShowLog()
{
    const auto log_manager = LogManager::GetLogManager();
    if (!log_manager)
    {
        assert(false);
        printf("log_managerがありません\n");
        return;
    }
    log_manager->ShowLog();
}

}   // namespace action_log