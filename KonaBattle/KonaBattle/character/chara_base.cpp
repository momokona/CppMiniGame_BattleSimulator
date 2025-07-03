#include"chara_base.h"
#include "../ui/ui_manager.h"
#include <cassert>
#include "../game_mode/log_manager.h"
#include "../defs/state_defs.h"




CharaBase::CharaBase(const std::string& NAME, const int MAX_HP, const int ATTACK, const int DEFENSE, const character::CharaType CHARA_TYPE)
	: NAME_(NAME)
	, MAX_HP_(MAX_HP)
	, attack_(ATTACK)
	, defense_(DEFENSE)
	, CHARA_TYPE_(CHARA_TYPE)
{}

CharaBase::~CharaBase()
{
}

void CharaBase::Initialize()
{
	hp_ = MAX_HP_;
	abnormal_states_info_.clear();
}


int CharaBase::SufferAttack(const int OPPONENT_ATTACK, const std::string& OPPONENT_NAME)
{
	// �_���[�W�̌v�Z
	const int DAMAGE = CalcDamage(OPPONENT_ATTACK, defense_);
	CalcHp(DAMAGE);
	ui::DispBattleInfo(DAMAGE, OPPONENT_NAME, NAME_, hp_);
	return DAMAGE;
}

void CharaBase::TurnEndProcess()
{
	// �h��͂����ɖ߂�
	if (behavior_ == BehaviorPattern::DEFENSE)
	{
		defense_ /= character::DEFENSE_MAGNIFICATION;
	}
	behavior_ = BehaviorPattern::INVALID;
}


void CharaBase::DefenseProcess()
{
	defense_ *= character::DEFENSE_MAGNIFICATION;
	ui::DispBehavior(BehaviorPattern::DEFENSE, NAME_);
}

void CharaBase::SetState(const character::State STATE)
{
	// NORMAL��ԂɃZ�b�g���ꂽ��S�Ă̏�Ԉُ��ł�����
	if(STATE == character::State::NORMAL)
	{
		abnormal_states_info_.clear();
	}
	else
	{
		// ��Ԃ̒��ɕ��ʂ��������ꍇ�͏���
		const auto it = abnormal_states_info_.find(character::State::NORMAL);
		if (it != abnormal_states_info_.end())
		{
			abnormal_states_info_.erase(it);
		}
		// �e�����󂯂�񐔂��Z�b�g
		abnormal_states_info_[STATE] = StateMap::GetStateMap()->GetTurnNum(STATE);

	}
	ui::DispNewState(STATE, NAME_);
}

//	��Ԃ𔽉f������(�������U�����󂯂鑤�̎��ɖ��񔽉f������)
void CharaBase::ReflectState()
{
	for (auto it = abnormal_states_info_.begin(); it != abnormal_states_info_.end();)
	{
		int damage{};
		// ����ł�����I��
		if (IsDead())
		{
			break;
		}
		if (it->first == character::State::NORMAL)
		{
			// ��Ԉُ�Ȃ��ꍇ�͒T���I��
			break;
		}

		// ��Ԉُ���ʂ𔽉f
		const auto EFFECT_FUNC = state_map::GetStateEffectFunc(it->first);
		EFFECT_FUNC(*this, damage);

		// ��Ԉُ�𔽉f�������ʂ�UI�ɏo��
		ui::DispReflectState(it->first, NAME_, damage, hp_);

		// ��Ԉُ�̎�������
		if (--it->second == 0)
		{
			it = abnormal_states_info_.erase(it);
		}
		else
		{
			++it;
		}
	}
}
// �h�䂵���Ƃ��ȊO�̏���
void CharaBase::Act(std::shared_ptr<CharaBase> target)
{
	if (!target)
	{
		assert(false);
		printf("�U������鑤�̃f�[�^������܂���\n");
		return;
	}
	const BehaviorPattern BEHAVIOR = GetNextBehavior();
	ActionLog log{ NAME_, target->GetName(), BEHAVIOR };
	if (BEHAVIOR == BehaviorPattern::DEFENSE)
	{
		action_log::AddLog(log);
		return;
	}

	ui::DispBehavior(GetNextBehavior(), NAME_);

	if (BEHAVIOR == BehaviorPattern::ATTACK)
	{
		const int DAMAGE = target->SufferAttack(attack_, NAME_);
		log.damage = DAMAGE;
	}
	else if(BEHAVIOR == BehaviorPattern::ITEM)
	{
		// �A�C�e�����g�������̏���������.�A�C�e���͖������Ȃ̂œłɂ��Ă���B
		log.added_state.push_back(character::State::POISON);
		target->SetState(character::State::POISON);

	}
	else if (BEHAVIOR == BehaviorPattern::POISON)
	{
		if (CHARA_TYPE_ == character::CharaType::PLAYER)
		{
			// �ōU�����g����͓̂G����
			assert(false);
			printf("ui_manager������܂���\n");
			return;
		}
		log.added_state.push_back(character::State::POISON);
		target->SetState(character::State::POISON);
	}
	action_log::AddLog(log);
}

void CharaBase::CalcHp(const int DAMAGE)
{
	hp_ -= DAMAGE;
	if (hp_ < 0)
	{
		hp_ = 0;
	}
}

const int CharaBase::CalcDamage(const int ATTACK, const int DEFENSE)
{
	return std::max(0, ATTACK * ATTACK_MULTIPLIER - DEFENSE);
}


