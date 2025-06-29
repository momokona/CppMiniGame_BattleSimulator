#include"chara_base.h"
#include "../ui/ui_manager.h"

constexpr int POISON_DAMAGE = 10;

CharaBase::CharaBase(const std::string NAME, const int MAX_HP, const int ATTACK, const int DEFENSE, const character::CharaType CHARA_TYPE)
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


void CharaBase::SufferAttack(const int OPPONENT_ATTACK, const std::string OPPONENT_NAME)
{
	// �_���[�W�̌v�Z
	const int DAMAGE = OPPONENT_ATTACK - defense_;
	CalcHp(DAMAGE);
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
	if (poison_state_num_ > 0)
	{
		if (--poison_state_num_ == 0)
		{
			states_.erase(character::State::POISON);
		}
	}
}

void CharaBase::SetState(character::State state)
{
	// NORMAL��ԂɃZ�b�g���ꂽ��S�Ă̏�Ԉُ��ł�����
	if(state == character::State::NORMAL)
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
	}
	states_.insert(state);
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
	const BehaviorPattern BEHAVIOR = GetNextBehavior();
	if (BEHAVIOR == BehaviorPattern::ATTACK)
	{
		target->SufferAttack(attack_, NAME_);
	}
	else if(BEHAVIOR == BehaviorPattern::ITEM)
	{
		// �A�C�e�����g�������̏���������
	}
	else if (BEHAVIOR == BehaviorPattern::POISON)
	{
		if (CHARA_TYPE_ == character::CharaType::PLAYER)
		{
			// �ōU�����g����͓̂G����
			// �A�T�[�g�����ɂ�������
			return;
		}
		target->SufferAttack(POISON_DAMAGE, NAME_);
		target->SetState(character::State::POISON);
	}
}

void CharaBase::CalcHp(const int DAMAGE)
{
	hp_ -= DAMAGE;
	if (IsDead())
	{
		hp_ = 0;
	}
}