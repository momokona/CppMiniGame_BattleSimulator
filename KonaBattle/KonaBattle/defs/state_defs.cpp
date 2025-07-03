#include"state_defs.h"
#include"../character/chara_base.h"
#include <cassert>

// 状態異常関数の登録
// TODO：状態異常を追加した場合にはここに書く
// 毒
RegesiterStateInfo state_poison_register(character::State::POISON, [](CharaBase& self, int& damage)
	{
		damage = POISON_DAMAGE;
		self.CalcHp(damage);
	}, POISON_NUM, "%sは毒で%dダメージを受けた！", "毒");


RegesiterStateInfo state_normal_register(character::State::NORMAL, nullptr, INT_MAX, "", "通常");




void StateMap::AddEntry(const character::State STATE, const AbnormalEffectFunc FUNC, const int TURN_NUM, const std::string& DAMAAGE_MESSAGE, const std::string& STATE_NAME)
{
	state_map_.emplace(STATE, StateInfo(FUNC, TURN_NUM, DAMAAGE_MESSAGE, STATE_NAME));
}

StateMap::AbnormalEffectFunc StateMap::GetStateEffectFunc(const character::State STATE) const
{
	const auto it = state_map_.find(STATE);
	if (it == state_map_.end())
	{
		assert(false);
		printf("指定された状態異常の関数は存在しません\n");
		return nullptr;
	}
	return it->second.effect_func;
}

std::string StateMap::GetDamageMessage(const character::State STATE) const
{
	const auto it = state_map_.find(STATE);
	if (it == state_map_.end())
	{
		assert(false);
		printf("指定された状態異常の関数は存在しません\n");
		return nullptr;
	}
	return it->second.damage_message;
}

std::string StateMap::GetStateName(const character::State STATE) const
{
	const auto it = state_map_.find(STATE);
	if (it == state_map_.end())
	{
		assert(false);
		printf("指定された状態異常の関数は存在しません\n");
		return nullptr;
	}
	return it->second.state_name;
}

RegesiterStateInfo::RegesiterStateInfo(const character::State STATE, StateMap::AbnormalEffectFunc FUNC, const int TURN_NUM, const std::string& DAMAAGE_MESSAGE, const std::string& STATE_NAME)
{
	const auto STATE_MAP = StateMap::GetStateMap();
	if (!STATE_MAP)
	{
		assert(false);
		printf("状態異常関数を登録できません\n");
		return;
	}
	STATE_MAP->AddEntry(STATE, FUNC, TURN_NUM, DAMAAGE_MESSAGE, STATE_NAME);

}


// 外部関数

StateMap::AbnormalEffectFunc state_map::GetStateEffectFunc(const character::State STATE)
{
	const auto STATE_MAP = StateMap::GetStateMap();
	if (!STATE_MAP)
	{
		return nullptr;
	}
	return STATE_MAP->GetStateEffectFunc(STATE);
}

std::string state_map::GetDamageMessage(const character::State STATE)
{
	const auto STATE_MAP = StateMap::GetStateMap();
	if (!STATE_MAP)
	{
		return nullptr;
	}
	return STATE_MAP->GetDamageMessage(STATE);
}

std::string state_map::GetStateName(const character::State STATE)
{
	const auto STATE_MAP = StateMap::GetStateMap();
	if (!STATE_MAP)
	{
		return nullptr;
	}
	return STATE_MAP->GetStateName(STATE);
}
