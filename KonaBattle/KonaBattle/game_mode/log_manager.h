#pragma once
#include <string>
#include <vector>
#include "../character/chara_base.h"
namespace game_mode
{
	

}	// namespace game_mode


struct ActionLog
{
    const std::string ATTACKER_NAME{};         // �s�������L������
    const std::string TARGET_NAME{};        // �ΏۃL�������i�ȗ��j
    const BehaviorPattern BEHAVIOR{}; // �s���̎�ށi�U���A�h��Ȃǁj
    int damage{};                 // �^�����_���[�W�i�U���̏ꍇ�j
    std::vector<character::State> added_state{}; // ��Ԉُ�i�łȂǁj
    ActionLog(const std::string ATTACKER_NAME, const std::string TARGET_NAME, const BehaviorPattern BEHAVIOR)
        :ATTACKER_NAME(ATTACKER_NAME)
        , TARGET_NAME(TARGET_NAME)
        , BEHAVIOR(BEHAVIOR) {}
};

class LogManager
{
public:
    void AddLog(const ActionLog& LOG)
    {
        behavior_log_.push_back(LOG);
    }
    void ShowLog() const;
    static LogManager* GetLogManager()
    {
        return log_manager_;
    }
private:
    // �R���X�g���N�^�̉B��
    LogManager() {};
    LogManager(const LogManager& obj) {};
    // �s���𕶎��ɒ���
    std::string BehaviorToString(BehaviorPattern pattern);
private:
    std::vector<ActionLog> behavior_log_{};	// �s������
    static LogManager* log_manager_{};
};

namespace log
{
void AddLog(const ActionLog& LOG);

}