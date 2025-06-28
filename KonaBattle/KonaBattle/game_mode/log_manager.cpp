#include "log_manager.h"
#include <iostream>

void BattleLogManager::ShowLog()
{
	for (const auto& log : behavior_log_)
	{
		// TODO:���O�̏o�͂�����
        const std::string BEHAVIIOR =  BehaviorToString(log.BEHAVIOR);
	}
}

std::string BattleLogManager::BehaviorToString(BehaviorPattern pattern)
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
