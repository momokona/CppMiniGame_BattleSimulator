#pragma once
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

private:
	CharacterManager() {};
	CharacterManager(const CharacterManager& other) {};
private:
	static CharacterManager* chara_manager_;
	
};