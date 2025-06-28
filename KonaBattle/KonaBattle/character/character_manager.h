#pragma once
#include "enemy.h"
#include "player.h"

class CharacterManager
{
public:
	void Initialize();
	// 唯一のインスタンスを作成
	static void Create();
	static void Delete();

	CharacterManager* GetCharacterManager()
	{
		return chara_manager_;
	}
	// 1ターンごとのリセット
	void SetParamForNextTurn();

private:
	CharacterManager() {};
	CharacterManager(const CharacterManager& other) {};
private:
	static CharacterManager* chara_manager_;
	Player* player_{};
	
};