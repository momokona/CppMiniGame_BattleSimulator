#include "ui_manager.h"
#include "../defs/defs.h"
#include <cassert>
#include "../game_mode/game_manager.h"
#include<conio.h>
#include "../character/character_manager.h"
#include "../defs/state_defs.h"
#include "../defs/behavior_defs.h"
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
	printf("%sは%dのダメージを受けた！\n", disp_info.defenser_name.c_str(), disp_info.damage);
	printf("%sの残りのHPは%dになった。\n", disp_info.defenser_name.c_str(), disp_info.hp);
	printf("\n");
	if (disp_info.hp <= 0)
	{
		printf("%sの負け！\n", disp_info.defenser_name.c_str());
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

	printf("%sの残りのHPは%dになった。\n", disp_info.defenser_name.c_str(), disp_info.hp);
	printf("\n");
	if (disp_info.hp <= 0)
	{
		printf("%sの負け！\n", disp_info.defenser_name.c_str());
	}
}


void UiManager::ShowActionOptions() const
{
	printf("\n\n");
	printf("%sのターン！どうする？\n", std::string(PLAYER_NAME).c_str());
	printf("1. 攻撃  2.  防御  3. アイテム\n");
	char input{};
	while (1)
	{
		input = _getch();
		
		const auto SELECTED_BEHAVIOR = behavior::GetSelectBehavior(input);
		if (SELECTED_BEHAVIOR != BehaviorPattern::INVALID)
		{
			character::SetChoiceAction(SELECTED_BEHAVIOR);
			break;
		}
		printf("1〜3を選択してください。\n");
	}
	system("cls");
}

void UiManager::DispBehavior(const BehaviorPattern BEHAVIOR, const std::string& ATTACKER_NAME)
{
	printf("\n");
	printf(behavior::GetMessage(BEHAVIOR).c_str(), ATTACKER_NAME.c_str());
}

void UiManager::DispEndGame() const
{
	printf("\n");
	printf("Thank you for Playing!!\n");
	// 入力待ち処理
}

void UiManager::DispTitle() const
{
	printf("コナの冒険\n");
	printf("これはトイプードルのコナが敵と戦うゲームです。\n");
	// 入力を待つ
	_getch();
	// 入力後に画面をクリアする
	system("cls");
	// 入力されたら
	game_manager::SetGameState(GameState::INGAME);
}

void UiManager::DispNewState(const character::State STATE, const std::string& NAME) const
{
	printf("%sは%s状態になった！\n", NAME.c_str(), state_map::GetStateName(STATE).c_str());
}



// 外部関数
namespace ui
{
void DispBattleInfo(const int DAMAGE, const std::string& ATTACKER_NAME, const std::string& DEFENSER_NAME, const int DEFENSER_HP)
{
	const auto ui_manager = UiManager::GetUiManager();
	if (!ui_manager)
	{
		assert(false);
		printf("ui_managerがありません\n");
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
		printf("ui_managerがありません\n");
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
		printf("ui_managerがありません\n");
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
		printf("ui_managerがありません\n");
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
		printf("ui_managerがありません\n");
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
		printf("ui_managerがありません\n");
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
		printf("ui_managerがありません\n");
		return;
	}
	ui_manager->DispNewState(STATE, NAME);
}
}	// namespace ui