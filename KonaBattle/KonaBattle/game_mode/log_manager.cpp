#include "log_manager.h"
#include <iostream>

void BattleLogManager::ShowLog()
{
	for (const auto& log : behavior_log_)
	{
		// TODO:ログの出力をする
        const std::string BEHAVIIOR =  BehaviorToString(log.BEHAVIOR);
	}
}

std::string BattleLogManager::BehaviorToString(BehaviorPattern pattern)
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
