#include "ui_manager.h"
#include "../defs/defs.h"
#include <cassert>
#include "../game_mode/game_manager.h"
#include<conio.h>
#include "../character/character_manager.h"
#include "../defs/state_defs.h"
UiManager* UiManager::ui_manager_ = nullptr;

void UiManager::Create()
{
	if (ui_manager_)
	{
		return;
	}
	ui_manager_ = new UiManager;
}


void UiManager::DispBattleInfo(const DispInfo& disp_info) const
{
	printf("%s��%d�̃_���[�W���󂯂��I\n", disp_info.defenser_name.c_str(), disp_info.damage);
	printf("%s�̎c���HP��%d�ɂȂ����B\n", disp_info.defenser_name.c_str(), disp_info.hp);
	printf("\n");
	if (disp_info.hp <= 0)
	{
		printf("%s�̕����I\n", disp_info.defenser_name.c_str());
	}
}

void UiManager::DispReflectState(const DispInfo& disp_info) const
{
	if (disp_info.state == character::State::NORMAL)
	{
		return;
	}
	const std::string damage_message = state_map::GetDamageMessage(disp_info.state);
	printf(damage_message.c_str(), disp_info.defenser_name.c_str(), disp_info.damage);

	printf("%s�̎c���HP��%d�ɂȂ����B\n", disp_info.defenser_name.c_str(), disp_info.hp);
	printf("\n");
	if (disp_info.hp <= 0)
	{
		printf("%s�̕����I\n", disp_info.defenser_name.c_str());
	}
}


void UiManager::ShowActionOptions() const
{
	printf("\n\n");
	printf("%s�̃^�[���I�ǂ�����H\n", std::string(PLAYER_NAME).c_str());
	printf("1. �U��  2.  �h��  3. �A�C�e��\n");
	while (1)
	{
		bool correct_choice = true;
		switch (_getch())
		{
		case '1':
			character::SetChoiceAction(BehaviorPattern::ATTACK);
			break;
		case '2':
			character::SetChoiceAction(BehaviorPattern::DEFENSE);
			break;
		case '3':
			character::SetChoiceAction(BehaviorPattern::ITEM);
			break;
		default:
			printf("1�`3��I�����Ă��������B\n");
			correct_choice = false;
			break;
		}
		if (correct_choice)
		{
			break;
		}
	}
	system("cls");
}

void UiManager::DispBehavior(const BehaviorPattern BEHAVIOR, const std::string& ATTACKER_NAME)
{
	printf("\n");
	switch (BEHAVIOR)
	{
	case BehaviorPattern::ATTACK:
		printf("%s�̍U���I\n", ATTACKER_NAME.c_str());
		break;
	case BehaviorPattern::ITEM:
		printf("%s�̓A�C�e�����g�����I�I\n", ATTACKER_NAME.c_str());
		printf("�A�C�e���͖������Ȃ̂œŏ�Ԃɂ��܂��B\n");
		break;
	case BehaviorPattern::DEFENSE:
		printf("%s�͐g��������I�I\n", ATTACKER_NAME.c_str());
		break;
	case BehaviorPattern::POISON:
		printf("%s�͓ōU�����d�|���Ă����I�I\n", ATTACKER_NAME.c_str());
		break;
	default:
		break;
	}
}

void UiManager::DispEndGame() const
{
	printf("\n");
	printf("Thank you for Playing!!\n");
	// ���͑҂�����
}

void UiManager::DispTitle() const
{
	printf("�R�i�̖`��\n");
	printf("����̓g�C�v�[�h���̃R�i���G�Ɛ키�Q�[���ł��B\n");
	// ���͂�҂�
	_getch();
	// ���͌�ɉ�ʂ��N���A����
	system("cls");
	// ���͂��ꂽ��
	game_manager::SetGameState(GameState::INGAME);
}

void UiManager::DispNewState(const character::State STATE, const std::string& NAME) const
{
	printf("%s��%s��ԂɂȂ����I\n", NAME.c_str(), state_map::GetStateName(STATE).c_str());
}



// �O���֐�
namespace ui
{
void DispBattleInfo(const int DAMAGE, const std::string& ATTACKER_NAME, const std::string& DEFENSER_NAME, const int DEFENSER_HP)
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

void ShowActionOptions()
{
	const auto ui_manager = UiManager::GetUiManager();
	if (!ui_manager)
	{
		assert(false);
		printf("ui_manager������܂���\n");
		return;
	}
	ui_manager->ShowActionOptions();
}

void DispBehavior(const BehaviorPattern behavior, const std::string& ATTACKER_NAME)
{
	const auto ui_manager = UiManager::GetUiManager();
	if (!ui_manager)
	{
		assert(false);
		printf("ui_manager������܂���\n");
		return;
	}
	ui_manager->DispBehavior(behavior, ATTACKER_NAME);
}

void DispReflectState(const character::State STATE, const std::string& NAME, const int DAMAGE, const int HP)
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

void DispNewState(const character::State STATE, const std::string& NAME)
{
	const auto ui_manager = UiManager::GetUiManager();
	if (!ui_manager)
	{
		assert(false);
		printf("ui_manager������܂���\n");
		return;
	}
	ui_manager->DispNewState(STATE, NAME);
}
}	// namespace ui