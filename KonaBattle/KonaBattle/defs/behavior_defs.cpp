#include "behavior_defs.h"
#include <cassert>
#include"../character/chara_base.h"
#include"../game_mode/log_manager.h"

BehaviorMap* BehaviorMap::GetBehaviorMap()
{
	static BehaviorMap instance;
	return &instance;
}

RegisterBehaviorInfo::RegisterBehaviorInfo(const BehaviorPattern BEHAVIOR, const BehaviorMap::ActFunc& ACT_FUNC, const char* KEY, const std::string& MESSAGE, const std::string& NAME)
{
	const auto MAP = BehaviorMap::GetBehaviorMap();
	if (!MAP)
	{
		assert(false);
		printf("�s���ɂ��Ă܂Ƃ߂���񂪂���܂���\n");
		return;
	}
	MAP->AddEntry(BEHAVIOR, ACT_FUNC, KEY, MESSAGE, NAME);
}


// �s�����o�^
// �U��
RegisterBehaviorInfo behavior_normal_info(BehaviorPattern::ATTACK, [](CharaBase& target, const int ATTACK, const std::string& NAME, ActionLog& log)
	{
		const int DAMAGE = target.SufferAttack(ATTACK, NAME);
		log.damage = DAMAGE;
	}, "1", "%s�̍U���I\n", "�U��");

// �h��
RegisterBehaviorInfo behavior_defense_info(BehaviorPattern::DEFENSE, [](CharaBase& target, const int ATTACK, const std::string& NAME, ActionLog& log)
	{
		action_log::AddLog(log);
	}, "2", "%s�͐g��������I�I\n", "�h��");

// �A�C�e��
RegisterBehaviorInfo behavior_item_info(BehaviorPattern::ITEM, [](CharaBase& target, const int ATTACK, const std::string& NAME, ActionLog& log)
	{
		// �A�C�e�����g�������̏���������.�A�C�e���͖������Ȃ̂œłɂ��Ă���B
		log.added_state.push_back(character::State::POISON);
		target.SetState(character::State::POISON);
	}, "3", "%s�̓A�C�e�����g�����I�I\n", "�A�C�e��");

// �ōU��
RegisterBehaviorInfo behavior_poison_info(BehaviorPattern::POISON, [](CharaBase& target, const int ATTACK, const std::string& NAME, ActionLog& log)
	{
		if (target.GetCharaType() == character::CharaType::ENEMY)
		{
			// �ōU�����g����͓̂G����
			assert(false);
			printf("ui_manager������܂���\n");
			return;
		}
		log.added_state.push_back(character::State::POISON);
		target.SetState(character::State::POISON);
	}, "", "%s�͓ōU�����d�|���Ă����I�I\n", "�ōU��");






// �O���֐�
BehaviorMap::ActFunc behavior::GetActFunc(const BehaviorPattern BEHAVIOR)
{
	const auto MAP = BehaviorMap::GetBehaviorMap();
	if (!MAP)
	{
		return nullptr;
	}
	return MAP->GetActFunc(BEHAVIOR);
}
const char* behavior::GetInputKey(const BehaviorPattern BEHAVIOR)
{
	const auto MAP = BehaviorMap::GetBehaviorMap();
	if (!MAP)
	{
		return nullptr;
	}
	return MAP->GetInputKey(BEHAVIOR);
}
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