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
	const auto ui_manager = UiManager::GetUiManager();
	if (!ui_manager)
	{
		return;
	}
	ui_manager->DispBattleInfo(DispInfo(OPPONENT_NAME, NAME_, DAMAGE, hp_));
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
}