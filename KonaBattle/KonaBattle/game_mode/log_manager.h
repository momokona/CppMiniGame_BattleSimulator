#pragma once
#include "../character/chara_base.h"
#include <string>
#include <vector>

struct ActionLog
{
    std::string attacker_name{};         // �s�������L������
    std::string target_name{};        // �ΏۃL�������i�ȗ��j
    BehaviorPattern behavior{}; // �s���̎�ށi�U���A�h��Ȃǁj
    int damage{};                 // �^�����_���[�W�i�U���̏ꍇ�j
    std::vector<character::State> added_state{}; // ��Ԉُ�i�łȂǁj
    ActionLog(std::string attacker_name, std::string target_name, const BehaviorPattern BEHAVIOR)
        :attacker_name(std::move(attacker_name))
        , target_name(std::move(target_name))
        , behavior(BEHAVIOR) {}
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
    void ShowRecentLog(const int NUM) const;

private:
    // �R���X�g���N�^�̉B��
    LogManager() {};
    LogManager(const LogManager& obj) = delete;
    // �s���𕶎��ɒ���
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

