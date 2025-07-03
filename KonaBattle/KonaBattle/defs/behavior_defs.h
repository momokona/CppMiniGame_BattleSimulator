#pragma once
#include <functional>
#include <string>
#include"defs.h"
// 前方宣言
class CharaBase;
struct ActionLog;

class BehaviorMap
{
public:
	using ActFunc = std::function<void(CharaBase&, const int, const std::string&, ActionLog& log)>;	// 行動したときに相手に及ぼす影響
	struct BehaviorInfo
	{
		ActFunc act_func;
		const char* input_key{};	// 対応する入力キー
		std::string behavior_message{};
		std::string behavior_name{};
		BehaviorInfo(const ActFunc& ACT_FUNC, const char* KEY, const std::string& MESSAGE, const std::string& NAME)
			:act_func(ACT_FUNC)
			, input_key(KEY)
			, behavior_message(MESSAGE)
			, behavior_name(NAME) {
		}
	};
	void AddEntry(const BehaviorPattern BEHAVIOR, const ActFunc& ACT_FUNC, const char* KEY, const std::string& MESSAGE, const std::string& NAME)
	{
		behavior_map_.emplace(BEHAVIOR, BehaviorInfo(ACT_FUNC, KEY, MESSAGE, NAME));
	}
	static BehaviorMap* GetBehaviorMap();
	ActFunc GetActFunc(const BehaviorPattern BEHAVIOR)
	{
		return behavior_map_.at(BEHAVIOR).act_func;
	}
	const char* GetInputKey(const BehaviorPattern BEHAVIOR)
	{
		return behavior_map_.at(BEHAVIOR).input_key;
	}
	std::string GetMessage(const BehaviorPattern BEHAVIOR)
	{
		return behavior_map_.at(BEHAVIOR).behavior_message;
	}
	std::string GetBehaviorName(const BehaviorPattern BEHAVIOR)
	{
		return behavior_map_.at(BEHAVIOR).behavior_name;
	}
private:
	std::unordered_map<BehaviorPattern, BehaviorInfo>behavior_map_{};

};

class RegisterBehaviorInfo
{
public:
	RegisterBehaviorInfo(const BehaviorPattern BEHAVIOR, const BehaviorMap::ActFunc& ACT_FUNC, const char* KEY, const std::string& MESSAGE, const std::string& NAME);
};

// 外部関数
namespace behavior
{
BehaviorMap::ActFunc GetActFunc(const BehaviorPattern BEHAVIOR);
const char* GetInputKey(const BehaviorPattern BEHAVIOR);
std::string GetMessage(const BehaviorPattern BEHAVIOR);
std::string GetBehaviorName(const BehaviorPattern BEHAVIOR);
}