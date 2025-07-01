#pragma once
#include "../character/chara_base.h"
#include <string>
#include <vector>

struct ActionLog
{
    const std::string ATTACKER_NAME{};         // �s�������L������
    const std::string TARGET_NAME{};        // �ΏۃL�������i�ȗ��j
    const BehaviorPattern BEHAVIOR{}; // �s���̎�ށi�U���A�h��Ȃǁj
    int damage{};                 // �^�����_���[�W�i�U���̏ꍇ�j
    std::vector<character::State> added_state{}; // ��Ԉُ�i�łȂǁj
    ActionLog(std::string attacker_name, std::string target_name, const BehaviorPattern BEHAVIOR)
        :ATTACKER_NAME(std::move(attacker_name))
        , TARGET_NAME(std::move(target_name))
        , BEHAVIOR(BEHAVIOR) {}
};

class LogManager
{
public:
    static void Create();
    static void Destroy()
    {
        delete log_manager_;
    }
    void AddLog(const ActionLog& LOG)
    {
        behavior_log_.push_back(LOG);
    }
    void ShowLog() const;
    static LogManager* GetLogManager()
    {
        return log_manager_;
    }
    void ShowRecentLog(const int NUM);

private:
    // �R���X�g���N�^�̉B��
    LogManager() {};
    LogManager(const LogManager& obj) {};
    // �s���𕶎��ɒ���
    const std::string BehaviorToString(const BehaviorPattern PATTERN) const;
    const std::string StateToString(const character::State STATE) const;
    void ShowOneLog(const ActionLog& log) const;
private:
    std::vector<ActionLog> behavior_log_{};	// �s������
    static LogManager* log_manager_;
};

namespace action_log
{
void AddLog(const ActionLog& LOG);
void ShowLog();
void ShowRecentLog(const int NUM);

}   // namespace action_log

