#include "log_manager.h"
#include <iostream>
#include"../defs.h"
#include <cassert>
LogManager* LogManager::log_manager_ = nullptr;

void LogManager::ShowLog() const
{
	for (const auto& log : behavior_log_)
	{
		// TODO:ログの出力をする
        const std::string BEHAVIIOR = BehaviorToString(log.BEHAVIOR);
	}
}

std::string LogManager::BehaviorToString(BehaviorPattern pattern)
{
    switch (pattern)
    {
    case BehaviorPattern::ATTACK:
        return "攻撃";
    case BehaviorPattern::DEFENSE:
        return "防御";
    case BehaviorPattern::ITEM:
        return "アイテム";
    default:
        return "不明";
    }
}


namespace log
{
void AddLog(const ActionLog& LOG)
{
    const auto log_manager = LogManager::GetLogManager();
    if (!log_manager)
    {
        assert(false);
        printf("ui_managerがありません\n");
        return;
    }
    log_manager->AddLog(LOG);
}


}