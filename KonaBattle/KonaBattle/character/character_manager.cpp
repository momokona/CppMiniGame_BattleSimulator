#include "character_manager.h"


CharacterManager* CharacterManager::chara_manager_ = nullptr;

void CharacterManager::Create()
{
	if (!chara_manager_)
	{
		return;
	}
	chara_manager_ = new CharacterManager;
}


void CharacterManager::Delete()
{
	delete chara_manager_;
}
