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
	printf("%s��%s��%d�̃_���[�W��^�����I\n", disp_info.ATTACKER_NAME, disp_info.DEFENSE_NAME, disp_info.DAMAGE);
	printf("%s�̎c���HP��%d�ɂȂ����B\n", disp_info.DEFENSE_NAME, disp_info.HP);
	if (disp_info.HP <= 0)
	{
		printf("%s�̕����I\n", disp_info.DEFENSE_NAME);
	}
}

void UiManager::ShowActionOptions() const
{
	printf("%s�̃^�[���I�ǂ�����H\n", PLAYER_NAME);
	printf("1. �U��  2.  �h��  3. �A�C�e��\n");
}
