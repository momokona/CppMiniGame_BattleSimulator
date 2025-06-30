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
    printf("**����܂Ƃ�**\n");
    printf("\n");
    for (const auto& log : behavior_log_)
	{
		// TODO:���O�̏o�͂�����
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

        printf("�U����:%s\n", log.ATTACKER_NAME.c_str());
        printf("�^�[�Q�b�g:%s\n", log.TARGET_NAME.c_str());
        printf("�s��:%s\n", BEHAVIIOR.c_str());
        if (!log.added_state.empty())
        {
            printf("�^������Ԉُ�F%s\n", state.c_str());
        }
        if (log.BEHAVIOR == BehaviorPattern::ATTACK || log.damage > 0)
        {
            printf("�^�����_���[�W�F%d\n", log.damage);
        }
        printf("\n");
	}
}

const std::string& LogManager::BehaviorToString(const BehaviorPattern PATTERN) const
{
    static const std::unordered_map<BehaviorPattern, std::string> BEHAVIOR_NAME_MAP =
    {
        {BehaviorPattern::ATTACK, "�U��"},
        {BehaviorPattern::DEFENSE, "�h��"},
        {BehaviorPattern::ITEM, "�A�C�e��"},
        {BehaviorPattern::POISON, "�ōU��"},
    };
    const auto it = BEHAVIOR_NAME_MAP.find(PATTERN);
    if (it != BEHAVIOR_NAME_MAP.end())
    {
        return it->second;
    }
    return "�s��";
}

const std::string& LogManager::StateToString(const character::State STATE) const
{
    static const std::unordered_map<character::State, std::string> STATE_NAME_MAP =
    {
        {character::State::NORMAL, "�ʏ�"},
        {character::State::POISON, "��"},
    };
    const auto it = STATE_NAME_MAP.find(STATE);
    if (it != STATE_NAME_MAP.end())
    {
        return it->second;
    }
    return "�s��";
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

}   // namespace action_log