#pragma once
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

private:
	CharacterManager() {};
	CharacterManager(const CharacterManager& other) {};
private:
	static CharacterManager* chara_manager_;
	
};