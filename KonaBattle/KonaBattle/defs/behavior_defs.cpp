#include "behavior_defs.h"
#include <cassert>
#include"../character/chara_base.h"
#include"../game_mode/log_manager.h"

BehaviorMap* BehaviorMap::GetBehaviorMap()
{
	static BehaviorMap instance;
	return &instance;
}

const BehaviorPattern BehaviorMap::GetSelectBehavior(const char INPUT_KEY)
{
	bool find_behavior = false;
	const auto it = std::find_if(behavior_map_.begin(), behavior_map_.end(), [&](const auto pair)
		{
			return pair.second.input_key == INPUT_KEY;
		});
	if (it != behavior_map_.end())
	{
		return it->first;
	}
	return BehaviorPattern::INVALID;
}

RegisterBehaviorInfo::RegisterBehaviorInfo(const BehaviorPattern BEHAVIOR, const BehaviorMap::ActFunc& ACT_FUNC, char KEY, const std::string& MESSAGE, const std::string& NAME)
{
	const auto MAP = BehaviorMap::GetBehaviorMap();
	if (!MAP)
	{
		assert(false);
		printf("行動についてまとめた情報がありません\n");
		return;
	}
	MAP->AddEntry(BEHAVIOR, ACT_FUNC, KEY, MESSAGE, NAME);
}

constexpr char INVALID_INPUT_KEY = '\0';
// 行動情報登録
// 攻撃
RegisterBehaviorInfo behavior_normal_info(BehaviorPattern::ATTACK, [](CharaBase& target, const int ATTACK, const std::string& NAME, ActionLog& log)
	{
		const int DAMAGE = target.SufferAttack(ATTACK, NAME);
		log.damage = DAMAGE;
	}, '1', "%sの攻撃！\n", "攻撃");

// 防御
RegisterBehaviorInfo behavior_defense_info(BehaviorPattern::DEFENSE, [](CharaBase& target, const int ATTACK, const std::string& NAME, ActionLog& log)
	{
		action_log::AddLog(log);
	}, '2', "%sは身を守った！！\n", "防御");

// アイテム
RegisterBehaviorInfo behavior_item_info(BehaviorPattern::ITEM, [](CharaBase& target, const int ATTACK, const std::string& NAME, ActionLog& log)
	{
		// アイテムを使った時の処理を書く.アイテムは未実装なので毒にしている。
		log.added_state.push_back(character::State::POISON);
		target.SetState(character::State::POISON);
	}, '3', "%sはアイテムを使った！！\n", "アイテム");

// 毒攻撃
RegisterBehaviorInfo behavior_poison_info(BehaviorPattern::POISON, [](CharaBase& target, const int ATTACK, const std::string& NAME, ActionLog& log)
	{
		if (target.GetCharaType() == character::CharaType::ENEMY)
		{
			// 毒攻撃を使えるのは敵だけ
			assert(false);
			printf("ui_managerがありません\n");
			return;
		}
		log.added_state.push_back(character::State::POISON);
		target.SetState(character::State::POISON);
	}, INVALID_INPUT_KEY, "%sは毒攻撃を仕掛けてきた！！\n", "毒攻撃");






// 外部関数
BehaviorMap::ActFunc behavior::GetActFunc(const BehaviorPattern BEHAVIOR)
{
	const auto MAP = BehaviorMap::GetBehaviorMap();
	if (!MAP)
	{
		return nullptr;
	}
	return MAP->GetActFunc(BEHAVIOR);
}
// 行動選択キーを取得
char behavior::GetInputKey(const BehaviorPattern BEHAVIOR)
{
	const auto MAP = BehaviorMap::GetBehaviorMap();
	if (!MAP)
	{
		return char{};
	}
	return MAP->GetInputKey(BEHAVIOR);
}

// 行動するときに出すメッセージを出す
std::string behavior::GetMessage(const BehaviorPattern BEHAVIOR)
{
	const auto MAP = BehaviorMap::GetBehaviorMap();
	if (!MAP)
	{
		return nullptr;
	}
	return MAP->GetMessage(BEHAVIOR);
}
std::string behavior::GetBehaviorName(const BehaviorPattern BEHAVIOR)
{
	const auto MAP = BehaviorMap::GetBehaviorMap();
	if (!MAP)
	{
		return nullptr;
	}
	return MAP->GetBehaviorName(BEHAVIOR);
}

const BehaviorPattern behavior::GetSelectBehavior(const char INPUT_KEY)
{
	const auto MAP = BehaviorMap::GetBehaviorMap();
	if (!MAP)
	{
		return BehaviorPattern::INVALID;
	}
	return MAP->GetSelectBehavior(INPUT_KEY);
}