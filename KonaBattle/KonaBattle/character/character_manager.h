#pragma once
#include "enemy.h"
#include "player.h"
#include <memory>

class CharacterManager
{
public:
	void Initialize();
	// �B��̃C���X�^���X���쐬
	static void Create();
	static void Destroy();

	static CharacterManager* GetCharacterManager()
	{
		return chara_manager_;
	}
	void Update();
	// ��Ԉُ�̔��f�ƍs��������
	void CharaActionOnTurn(const std::shared_ptr<CharaBase>& ATTACKER, const std::shared_ptr<CharaBase>& TARGET, bool& death);


	// �I�����Z�b�g����
	void SetChoiceToPc(const BehaviorPattern behavior) const;

private:
	CharacterManager() {};
	CharacterManager(const CharacterManager& other) {};
	void DefenseProcess();
	// 1�^�[�����Ƃ̃��Z�b�g
	void TurnEndProcess();
private:
	static CharacterManager* chara_manager_;
	std::shared_ptr<Player> player_{};
	std::vector<std::shared_ptr<Enemy>> enemies_{};
};
namespace character
{
// �O���֐�
void SetChoiceAction(const BehaviorPattern behavior);
void Update();
void Initialize();
}