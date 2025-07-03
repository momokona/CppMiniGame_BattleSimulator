#pragma once
#include "enemy.h"
#include "player.h"
#include <memory>

class CharacterManager
{
public:
	void Initialize();
	// 唯一のインスタンスを作成
	static void Create();
	static void Destroy();

	static CharacterManager* GetCharacterManager()
	{
		return chara_manager_;
	}
	void Update();
	// 状態異常の反映と行動をする
	void CharaActionOnTurn(const std::shared_ptr<CharaBase>& ATTACKER, const std::shared_ptr<CharaBase>& TARGET, bool& death);


	// 選択をセットする
	void SetChoiceToPc(const BehaviorPattern behavior) const;

private:
	CharacterManager() {};
	CharacterManager(const CharacterManager& other) {};
	void DefenseProcess();
	// 1ターンごとのリセット
	void TurnEndProcess();
private:
	static CharacterManager* chara_manager_;
	std::shared_ptr<Player> player_{};
	std::vector<std::shared_ptr<Enemy>> enemies_{};
};
namespace character
{
// 外部関数
void SetChoiceAction(const BehaviorPattern behavior);
void Update();
void Initialize();
}