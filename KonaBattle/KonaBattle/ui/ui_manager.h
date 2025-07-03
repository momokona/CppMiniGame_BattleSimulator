#pragma once
#include <string>
#include "../character/chara_base.h"
struct DispInfo
{
	std::string attacker_name{};
	std::string defenser_name{};
	int damage{};
	int hp{};
	character::State state{ character::State::NORMAL };
};

class UiManager
{
public:
	static void Create();
	static void Destroy()
	{
		delete ui_manager_;
	}
	static UiManager* GetUiManager()
	{
		return ui_manager_;
	}
	void DispBattleInfo(const DispInfo& disp_info) const;
	void DispReflectState(const DispInfo& disp_info) const;
	void ShowActionOptions() const;
	void DispBehavior(const BehaviorPattern BEHAVIOR, const std::string& ATTACKER_NAME);
	void DispEndGame() const;
	void DispTitle() const;
	void DispNewState(const character::State STATE, const std::string& NAME) const;
private:
	UiManager() {}
	UiManager(const UiManager&) = delete;
	UiManager& operator=(const UiManager&) = delete;
private:
	static UiManager* ui_manager_;
};

// �O���֐�
namespace ui
{
// �o�g���̌��ʂ��o��
void DispBattleInfo(const int DAMAGE, const std::string& ATTACKER_NAME, const std::string& DEFENSER_NAME, const int DEFENSER_HP);
void ShowActionOptions();
void DispBehavior(const BehaviorPattern behavior, const std::string& ATTACKER_NAME);

// ��Ԉُ�𔽉f�������Ƃ��̌��ʂ��o��
void DispReflectState(const character::State STATE, const std::string& NAME, const int DAMAGE, const int HP);
// �Q�[���I�����ɏo�����b�Z�[�W
void DispEndGame();
void DispTitle();
void DispNewState(const character::State STATE, const std::string& NAME);
}	// namespace ui

