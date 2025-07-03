#pragma once
enum class GameState
{
	TITLE = 0,
	INGAME,
	JUST_END,
	END,
};
class GameManager
{
public:
	static void Create();
	static void Destroy();
	static GameManager* GetGameManager()
	{
		return game_manager_;
	}
	void Update();
	void SetState(const GameState state)
	{
		state_ = state;
	}
	const GameState GetState() const
	{
		return state_;
	}
private:
	GameManager() {};
	GameManager(const GameManager&) {};
	void EndGame();
private:
	static GameManager* game_manager_;
	GameState state_{ GameState::TITLE };
};

namespace game_manager
{
void SetGameState(const GameState state);
const GameState GetGameState();
void Update();
}	// namespace game_manager