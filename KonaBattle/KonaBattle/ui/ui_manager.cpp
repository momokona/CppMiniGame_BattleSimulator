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
	printf("%sの攻撃！\n", disp_info.attacker_name);
	printf("%sに%dのダメージを与えた！\n", disp_info.defenser_name, disp_info.damage);
	printf("%sの残りのHPは%dになった。\n", disp_info.defenser_name, disp_info.hp);
	if (disp_info.hp <= 0)
	{
		printf("%sの負け！\n", disp_info.defenser_name);
	}
}

void UiManager::DispReflectState(const DispInfo& disp_info) const
{
	switch (disp_info.state)
	{
	case character::State::NORMAL:
		return;
	case character::State::POISON:
		printf("%sは毒によって%dダメージを受けた！\n", disp_info.defenser_name, disp_info.damage);
		break;
	default:
		break;
	}
	printf("%sの残りのHPは%dになった。\n", disp_info.defenser_name, disp_info.hp);
	if (disp_info.hp <= 0)
	{
		printf("%sの負け！\n", disp_info.defenser_name);
	}
}

void UiManager::ShowActionOptions() const
{
	printf("%sのターン！どうする？\n", PLAYER_NAME);
	printf("1. 攻撃  2.  防御  3. アイテム\n");
	// なんかしらの入力を待つ処理
	// 入力後にプレイヤーに選択をセットする
}

void UiManager::DispEndGame() const
{
	printf("Thank you for Playing!!\n");
	// 入力待ち処理
}

void UiManager::DispTitle() const
{
	printf("コナの冒険\n");
	printf("これはトイプードルのコナが敵と戦うゲームです\n");
	// 入力を待つ
	// 入力後に画面をクリアする
	// 入力されたら
	game_manager::SetGameState(GameState::INGAME);
}



// 外部関数
namespace ui
{
void ui::DispBattleInfo(const int DAMAGE, const std::string ATTACKER_NAME, const std::string DEFENSER_NAME, const int DEFENSER_HP)
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

void DispReflectState(const character::State STATE, const std::string NAME, const int DAMAGE, const int HP)
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
}	// namespace ui