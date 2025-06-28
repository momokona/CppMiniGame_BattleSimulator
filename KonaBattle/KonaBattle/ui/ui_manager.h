#pragma once
#include <string>
struct DispInfo
{
	const std::string ATTACKER_NAME{};
	const std::string DEFENSE_NAME{};
	const int DAMAGE{};
	const int HP{};
	const bool IS_PLAYER_ATTACK{ false };
	DispInfo(const std::string ATTACKER_NAME, const std::string DEFENSE_NAME,
		const int DAMAGE, const int HP)
		: ATTACKER_NAME(ATTACKER_NAME)
		, DEFENSE_NAME(DEFENSE_NAME)
		, DAMAGE(DAMAGE)
		, HP(HP)
	{}
};

class UiManager
{
public:
	static void Create();
	static void Delete()
	{
		delete ui_manager_;
	}
	static UiManager* GetUiManager()
	{
		return ui_manager_;
	}
	void DispBattleInfo(const DispInfo& disp_info) const;
	void ShowActionOptions() const;
private:
	UiManager() {}
	UiManager(const UiManager&) {}
private:
	static UiManager* ui_manager_;
};