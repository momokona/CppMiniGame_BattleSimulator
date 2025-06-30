#include "game_manager.h"
#include <cassert>
#include<iostream>
#include "../ui/ui_manager.h"
#include "../character/character_manager.h"
#include "log_manager.h"
GameManager* GameManager::game_manager_ = nullptr;
void GameManager::Create()
{
	if (game_manager_)
	{
		return;
	}
	game_manager_ = new GameManager;
}


void GameManager::Destroy()
{
	delete game_manager_;
}

void GameManager::Update()
{
	switch (state_)
	{
	case GameState::TITLE:
		ui::DispTitle();
			break;
	case GameState::INGAME:
		ui::ShowActionOptions();
		character::Update();
			break;
	case GameState::JUST_END:
		ui::DispEndGame();
		action_log::ShowLog();
		state_ = GameState::END;
		break;

	}
}

namespace game_manager
{
void game_manager::SetGameState(const GameState state)
{
	auto game_manager = GameManager::GetGameManager();
	if (!game_manager)
	{
		assert(false);
		printf("game_manager‚ª‚ ‚è‚Ü‚¹‚ñ\n");
		return;
	}
	game_manager->SetState(state);
}
const GameState GetGameState()
{
	auto game_manager = GameManager::GetGameManager();
	if (!game_manager)
	{
		assert(false);
		printf("game_manager‚ª‚ ‚è‚Ü‚¹‚ñ\n");
		return GameState();
	}
	return game_manager->GetState();
}

void Update()
{
	auto game_manager = GameManager::GetGameManager();
	if (!game_manager)
	{
		assert(false);
		printf("game_manager‚ª‚ ‚è‚Ü‚¹‚ñ\n");
		return;
	}
	game_manager->Update();
}
}	// namespace game_manager