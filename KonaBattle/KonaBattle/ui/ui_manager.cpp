#include "ui_manager.h"
#include "../defs.h"
#include <cassert>
#include "../game_mode/game_manager.h"
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
	printf("%s�̍U���I\n", disp_info.attacker_name);
	printf("%s��%d�̃_���[�W��^�����I\n", disp_info.defenser_name, disp_info.damage);
	printf("%s�̎c���HP��%d�ɂȂ����B\n", disp_info.defenser_name, disp_info.hp);
	if (disp_info.hp <= 0)
	{
		printf("%s�̕����I\n", disp_info.defenser_name);
	}
}

void UiManager::DispReflectState(const DispInfo& disp_info) const
{
	switch (disp_info.state)
	{
	case character::State::NORMAL:
		return;
	case character::State::POISON:
		printf("%s�͓łɂ����%d�_���[�W���󂯂��I\n", disp_info.defenser_name, disp_info.damage);
		break;
	default:
		break;
	}
	printf("%s�̎c���HP��%d�ɂȂ����B\n", disp_info.defenser_name, disp_info.hp);
	if (disp_info.hp <= 0)
	{
		printf("%s�̕����I\n", disp_info.defenser_name);
	}
}

void UiManager::ShowActionOptions() const
{
	printf("%s�̃^�[���I�ǂ�����H\n", PLAYER_NAME);
	printf("1. �U��  2.  �h��  3. �A�C�e��\n");
	// �Ȃ񂩂���̓��͂�҂���
	// ���͌�Ƀv���C���[�ɑI�����Z�b�g����
}

void UiManager::DispEndGame() const
{
	printf("Thank you for Playing!!\n");
	// ���͑҂�����
}

void UiManager::DispTitle() const
{
	printf("�R�i�̖`��\n");
	printf("����̓g�C�v�[�h���̃R�i���G�Ɛ키�Q�[���ł�\n");
	// ���͂�҂�
	// ���͌�ɉ�ʂ��N���A����
	// ���͂��ꂽ��
	game_manager::SetGameState(GameState::INGAME);
}



// �O���֐�
namespace ui
{
void ui::DispBattleInfo(const int DAMAGE, const std::string ATTACKER_NAME, const std::string DEFENSER_NAME, const int DEFENSER_HP)
{
	const auto ui_manager = UiManager::GetUiManager();
	if (!ui_manager)
	{
		assert(false);
		printf("ui_manager������܂���\n");
		return;
	}
	DispInfo disp_info;
	disp_info.attacker_name = ATTACKER_NAME;
	disp_info.defenser_name = DEFENSER_NAME;
	disp_info.damage = DAMAGE;
	disp_info.hp = DEFENSER_HP;
	ui_manager->DispBattleInfo(disp_info);
}

void DispReflectState(const character::State STATE, const std::string NAME, const int DAMAGE, const int HP)
{
	const auto ui_manager = UiManager::GetUiManager();
	if (!ui_manager)
	{
		assert(false);
		printf("ui_manager������܂���\n");
		return;
	}
	DispInfo disp_info;
	disp_info.state = STATE;
	disp_info.defenser_name = NAME;
	disp_info.damage = DAMAGE;
	disp_info.hp = HP;
	ui_manager->DispReflectState(disp_info);
}

void DispEndGame()
{
	const auto ui_manager = UiManager::GetUiManager();
	if (!ui_manager)
	{
		assert(false);
		printf("ui_manager������܂���\n");
		return;
	}
	ui_manager->DispEndGame();
}

void DispTitle()
{
	const auto ui_manager = UiManager::GetUiManager();
	if (!ui_manager)
	{
		assert(false);
		printf("ui_manager������܂���\n");
		return;
	}
	ui_manager->DispTitle();
}
}	// namespace ui