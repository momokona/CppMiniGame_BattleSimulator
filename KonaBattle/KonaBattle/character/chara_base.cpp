#include"chara_base.h"

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
	printf("%s��%s��%d�̃_���[�W��^�����I\n", OPPONENT_NAME, NAME_, DAMAGE);
	CalcHp(DAMAGE);
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

//	��Ԃ𔽉f������
void CharaBase::ReflectState()
{
	for (const auto state : states_)
	{
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
			CalcHp(POISON_DAMAGE);
		}
	}
}

void CharaBase::CalcHp(const int DAMAGE)
{
	hp_ -= DAMAGE;
	if (IsDead())
	{
		hp_ = 0;
	}
	printf("%s�̎c���HP��%d�ɂȂ����B\n", NAME_, hp_);
	if (IsDead())
	{
		printf("%s�̕����I\n", NAME_, hp_);
	}
}