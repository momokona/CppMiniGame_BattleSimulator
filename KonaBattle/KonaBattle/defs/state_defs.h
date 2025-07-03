#pragma once
#include <functional>
#include <string>

// �O���錾
class CharaBase;
namespace character
{
	enum class State : int;  //  �O���錾�ɂ́u���^�iint�Ȃǁj�v���K�v�I
}

// ��ԂɊ֘A��������܂Ƃ߂�Map
// GameManager�ŌĂԂ̂�������������Create�֐��Ƃ��͍��Ȃ����j�ɂ���
class StateMap
{
public:
	using AbnormalEffectFunc = std::function<void(CharaBase&, int& damage)>;	// CharaBase*�^�������Ƃ��Ď��Avoid�^���߂�l�̊֐�
	struct StateInfo
	{
		AbnormalEffectFunc effect_func;	// ���ʊ֐�
		int turn_num{};	// �e����^����^�[����
		std::string damage_message{};	// �_���[�W���󂯂����̃��b�Z�[�W
		std::string state_name{};	// ��Ԉُ�̖��O
		StateInfo(const AbnormalEffectFunc EFFECT_FUNC, const int TURN_NUM
			, const std::string& DAMAGE_MESSAGE, const std::string& MESSAGE)
			: effect_func(EFFECT_FUNC)
			, turn_num(TURN_NUM)
			, damage_message(DAMAGE_MESSAGE)
			, state_name(MESSAGE)
		{
		}
	};
	// �֐��̓o�^
	void AddEntry(const character::State STATE, const AbnormalEffectFunc FUNC, const int TURN_NUM, const std::string& DAMAAGE_MESSAGE, const std::string& STATE_NAME);
	static StateMap* GetStateMap()
	{
		static StateMap instance;
		return &instance;
	}
	// ��Ԉُ�֐���T��
	AbnormalEffectFunc GetStateEffectFunc(const character::State STATE) const;
	std::string GetDamageMessage(const character::State STATE) const;
	std::string GetStateName(const character::State STATE) const;
	// �e�����󂯂�^�[������T��
	int GetTurnNum(const character::State STATE) const
	{
		return state_map_.at(STATE).turn_num;
	}
private:
	// �V���O���g���ɂ��邽�߂ɃR���X�g���N�^�͔���J
	StateMap() {};
	StateMap(const StateMap&) = delete;

private:
	std::unordered_map<character::State, StateInfo> state_map_{};
};

// ��Ԉُ�֐��o�^�p�̃N���X
// ���̃N���X�̃C���X�^���X��錾���邾���Ŋ֐����o�^�����
class RegesiterStateInfo
{
public:
	RegesiterStateInfo(const character::State STATE, StateMap::AbnormalEffectFunc FUNC, const int TURN_NUM, const std::string& DAMAAGE_MESSAGE, const std::string& STATE_NAME);

};

// �O���֐�
namespace state_map
{
StateMap::AbnormalEffectFunc GetStateEffectFunc(const character::State STATE);
std::string GetDamageMessage(const character::State STATE);
std::string GetStateName(const character::State STATE);
}