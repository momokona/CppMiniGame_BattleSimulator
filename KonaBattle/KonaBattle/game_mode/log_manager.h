#pragma once
#include <string>
#include <vector>
#include "../character/chara_base.h"
namespace game_mode
{
	

}	// namespace game_mode

// �s���p�^�[��(���O�p)
enum class BehaviorPattern
{
	ATTACK = 0,	// �U��
	DEFENSE,	// �h��
	ITEM,		// �A�C�e��
};
struct ActionLog
{
    const std::string ACtOR_NAME;         // �s�������L������
    const BehaviorPattern BEHAVIOR; // �s���̎�ށi�U���A�h��Ȃǁj
    const std::string TARGET_NAME;        // �ΏۃL�������i�ȗ��j
    const int DAMAGE{};                 // �^�����_���[�W�i�U���̏ꍇ�j
    std::vector<character::State> ADDED_STATES{}; // ��Ԉُ�i�łȂǁj

};

class BattleLogManager
{
public:
    void AddLog(ActionLog& log)
    {
        behavior_log_.push_back(log);
    }
    void ShowLog();
private:
    // �R���X�g���N�^�̉B��
    BattleLogManager() {};
    BattleLogManager(const BattleLogManager& obj) {};
    // �s���𕶎��ɒ���
    std::string BehaviorToString(BehaviorPattern pattern);
private:
    std::vector<ActionLog> behavior_log_{};	// �s������
};