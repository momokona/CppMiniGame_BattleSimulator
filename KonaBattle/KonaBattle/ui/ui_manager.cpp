#include "ui_manager.h"
#include "../defs.h"
UiManager* UiManager::ui_manager_ = nullptr;

void UiManager::Create()
{
	if (!ui_manager_)
	{
		return;
	}
	ui_manager_ = new UiManager;
}


void UiManager::DispBattleInfo(const DispInfo& disp_info) const
{
	printf("%sは%sに%dのダメージを与えた！\n", disp_info.ATTACKER_NAME, disp_info.DEFENSE_NAME, disp_info.DAMAGE);
	printf("%sの残りのHPは%dになった。\n", disp_info.DEFENSE_NAME, disp_info.HP);
	if (disp_info.HP <= 0)
	{
		printf("%sの負け！\n", disp_info.DEFENSE_NAME);
	}
}

void UiManager::ShowActionOptions() const
{
	printf("%sのターン！どうする？\n", PLAYER_NAME);
	printf("1. 攻撃  2.  防御  3. アイテム\n");
}
