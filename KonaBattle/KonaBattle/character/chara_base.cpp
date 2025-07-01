#include"chara_base.h"
#include "../ui/ui_manager.h"
#include <cassert>
#include "../game_mode/log_manager.h"

constexpr int POISON_DAMAGE = 10;
constexpr int POISON_NUM = 3;

CharaBase::CharaBase(const std::string& NAME, const int MAX_HP, const int ATTACK, const int DEFENSE, const character::CharaType CHARA_TYPE)
	: NAME_(NAME)
	, MAX_HP_(MAX_HP)
	, attack_(ATTACK)
	, defense_(DEFENSE)
	, CHARA_TYPE_(CHARA_TYPE)
{
	Initialize();
}

CharaBase::~CharaBase()
{
}

void CharaBase::Initialize()
{
	hp_ = MAX_HP_;
	states_.clear();
}


void CharaBase::SufferAttack(const int OPPONENT_ATTACK, const std::string& OPPONENT_NAME, ActionLog& log)
{
	// �_���[�W�̌v�Z
	const int DAMAGE = CalcDamage(OPPONENT_ATTACK, defense_);
	CalcHp(DAMAGE);
	log.damage = DAMAGE;
	ui::DispBattleInfo(DAMAGE, OPPONENT_NAME, NAME_, hp_);
}

void CharaBase::TurnEndProcess()
{
	// �h��͂����ɖ߂�
	if (behavior_ == BehaviorPattern::DEFENSE)
	{
		defense_ /= character::DEFENSE_MAGNIFICATION;
	}

	// ��Ԉُ�E�ł̏���
	for(auto abnormal_state_info : abnormal_states_info_)
	{
		if (--abnormal_state_info.second == 0)
		{
			states_.erase(character::State::POISON);
		}
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
		states_.clear();
	}
	else
	{
		// ��Ԃ̒��ɕ��ʂ��������ꍇ�͏���
		const auto it = states_.find(character::State::NORMAL);
		if (it != states_.end())
		{
			states_.erase(it);
		}
		// �ł̉񐔂��Z�b�g
		if (STATE == character::State::POISON)
		{
			abnormal_states_info_[character::State::POISON] = POISON_NUM;
		}
	}
	states_.insert(STATE);
	ui::DispNewState(STATE, NAME_);
}

//	��Ԃ𔽉f������(�������U�����󂯂鑤�̎��ɖ��񔽉f������)
void CharaBase::ReflectState()
{
	for (const auto state : states_)
	{
		int damage{};
		// ����ł�����I��
		if (IsDead())
		{
			break;
		}
		if (state == character::State::NORMAL)
		{
			// ��Ԉُ�Ȃ��ꍇ�͒T���I��
			break;
		}
		else if (state == character::State::POISON)
		{
			// �ŏ�Ԃ̎��̓_���[�W���󂯂�
			damage = POISON_DAMAGE;
			CalcHp(damage);
		}
		// ��Ԉُ�𔽉f�������ʂ�UI�ɏo��
		ui::DispReflectState(character::State::POISON, NAME_, damage, hp_);
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
		target->SufferAttack(attack_, NAME_, log);
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
	if (IsDead())
	{
		hp_ = 0;
	}
}

const int CharaBase::CalcDamage(const int ATTACK, const int DEFENSE)
{
	return std::max(0, ATTACK * ATTACK_MULTIPLIER - DEFENSE);
}
