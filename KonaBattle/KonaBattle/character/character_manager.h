#pragma once
#include "enemy.h"
#include "player.h"

class CharacterManager
{
public:
	void Initialize();
	// �B��̃C���X�^���X���쐬
	static void Create();
	static void Delete();

	CharacterManager* GetCharacterManager()
	{
		return chara_manager_;
	}
	// 1�^�[�����Ƃ̃��Z�b�g
	void SetParamForNextTurn();

private:
	CharacterManager() {};
	CharacterManager(const CharacterManager& other) {};
private:
	static CharacterManager* chara_manager_;
	Player* player_{};
	
};