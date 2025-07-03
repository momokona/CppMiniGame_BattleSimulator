#pragma once
#include <functional>
#include <string>

// 前方宣言
class CharaBase;
namespace character
{
	enum class State : int;  //  前方宣言には「基底型（intなど）」が必要！
}

// 状態に関連する情報をまとめたMap
// GameManagerで呼ぶのもおかしいからCreate関数とかは作らない方針にする
class StateMap
{
public:
	using AbnormalEffectFunc = std::function<void(CharaBase&, int& damage)>;	// CharaBase*型を引数として取り、void型が戻り値の関数
	struct StateInfo
	{
		AbnormalEffectFunc effect_func;	// 効果関数
		int turn_num{};	// 影響を与えるターン数
		std::string damage_message{};	// ダメージを受けた時のメッセージ
		std::string state_name{};	// 状態異常の名前
		StateInfo(const AbnormalEffectFunc EFFECT_FUNC, const int TURN_NUM
			, const std::string& DAMAGE_MESSAGE, const std::string& MESSAGE)
			: effect_func(EFFECT_FUNC)
			, turn_num(TURN_NUM)
			, damage_message(DAMAGE_MESSAGE)
			, state_name(MESSAGE)
		{
		}
	};
	// 関数の登録
	void AddEntry(const character::State STATE, const AbnormalEffectFunc FUNC, const int TURN_NUM, const std::string& DAMAAGE_MESSAGE, const std::string& STATE_NAME);
	static StateMap* GetStateMap()
	{
		static StateMap instance;
		return &instance;
	}
	// 状態異常関数を探す
	AbnormalEffectFunc GetStateEffectFunc(const character::State STATE) const;
	std::string GetDamageMessage(const character::State STATE) const;
	std::string GetStateName(const character::State STATE) const;
	// 影響を受けるターン数を探す
	int GetTurnNum(const character::State STATE) const
	{
		return state_map_.at(STATE).turn_num;
	}
private:
	// シングルトンにするためにコンストラクタは非公開
	StateMap() {};
	StateMap(const StateMap&) = delete;

private:
	std::unordered_map<character::State, StateInfo> state_map_{};
};

// 状態異常関数登録用のクラス
// このクラスのインスタンスを宣言するだけで関数が登録される
class RegesiterStateInfo
{
public:
	RegesiterStateInfo(const character::State STATE, StateMap::AbnormalEffectFunc FUNC, const int TURN_NUM, const std::string& DAMAAGE_MESSAGE, const std::string& STATE_NAME);

};

// 外部関数
namespace state_map
{
StateMap::AbnormalEffectFunc GetStateEffectFunc(const character::State STATE);
std::string GetDamageMessage(const character::State STATE);
std::string GetStateName(const character::State STATE);
}