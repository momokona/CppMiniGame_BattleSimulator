#include "log_manager.h"
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <algorithm>
#include"../defs/defs.h"
#include "../defs/state_defs.h"
#include "../defs/behavior_defs.h"
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
    printf("**����܂Ƃ�**\n");
    printf("\n");
    for (const auto& log : behavior_log_)
    {
        ShowOneLog(log);
    }
}

void LogManager::ShowOneLog(const ActionLog& log) const
{
    const std::string BEHAVIIOR = behavior::GetBehaviorName(log.behavior);
    std::string state_str{};
    for (const auto add_state : log.added_state)
    {
        if (state_str != "")
        {
            state_str += ", ";
        }
        state_str += state_map::GetStateName(add_state);
    }

    printf("�U����:%s\n", log.attacker_name.c_str());
    printf("�^�[�Q�b�g:%s\n", log.target_name.c_str());
    printf("�s��:%s\n", BEHAVIIOR.c_str());
    if (!state_str.empty())
    {
        printf("�^������Ԉُ�F%s\n", state_str.c_str());
    }
    if (log.behavior == BehaviorPattern::ATTACK || log.damage > 0)
    {
        printf("�^�����_���[�W�F%d\n", log.damage);
    }
    printf("\n");
}

void LogManager::ShowRecentLog(const int NUM) const
{
    // �͈͊O�ɂȂ�Ȃ��悤��
    auto it_begin = behavior_log_.begin();
    if (behavior_log_.size() > NUM)
    {
        it_begin = behavior_log_.end() - NUM;
    }

    std::for_each(it_begin, behavior_log_.end(), [&](const auto LOG)
        {
            ShowOneLog(LOG);
        });
}


namespace action_log
{
void AddLog(const ActionLog& LOG)
{
    const auto log_manager = LogManager::GetLogManager();
    if (!log_manager)
    {
        assert(false);
        printf("log_manager������܂���\n");
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
        printf("log_manager������܂���\n");
        return;
    }
    log_manager->ShowLog();
}

void ShowRecentLog(const int NUM)
{
    const auto log_manager = LogManager::GetLogManager();
    if (!log_manager)
    {
        assert(false);
        printf("log_manager������܂���\n");
        return;
    }
    log_manager->ShowRecentLog(NUM);
}

}   // namespace action_log