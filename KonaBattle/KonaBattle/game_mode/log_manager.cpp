#include "log_manager.h"
#include <iostream>
#include"../defs.h"
#include <cassert>
LogManager* LogManager::log_manager_ = nullptr;

void LogManager::ShowLog() const
{
	for (const auto& log : behavior_log_)
	{
		// TODO:���O�̏o�͂�����
        const std::string BEHAVIIOR = BehaviorToString(log.BEHAVIOR);
	}
}

std::string LogManager::BehaviorToString(BehaviorPattern pattern)
{
    switch (pattern)
    {
    case BehaviorPattern::ATTACK:
        return "�U��";
    case BehaviorPattern::DEFENSE:
        return "�h��";
    case BehaviorPattern::ITEM:
        return "�A�C�e��";
    default:
        return "�s��";
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
        printf("ui_manager������܂���\n");
        return;
    }
    log_manager->AddLog(LOG);
}


}