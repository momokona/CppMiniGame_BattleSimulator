#include "character_manager.h"
#include <cassert>
#include "../game_mode/game_manager.h"
#include "../ui/ui_manager.h"
constexpr int MAX_ENEMY_NUM = 10;

CharacterManager* CharacterManager::chara_manager_ = nullptr;

void CharacterManager::Initialize()
{
    player_ = std::make_shared<Player>(std::string(PLAYER_NAME), PLAYER_MAX_HP, PLAYER_INIT_ATTACK, PLAYER_INIT_DEFENSE);
    player_->Initialize();
    enemies_.reserve(MAX_ENEMY_NUM);
    // とりあえず一体だけデータ登録
    enemies_.push_back(std::make_shared<Enemy>(std::string(ENEMY1_NAME), ENEMY1_MAX_HP, ENEMY1_INIT_ATTACK, ENEMY1_INIT_DEFENSE));
    enemies_.back()->Initialize();
}



void CharacterManager::DefenseProcess()
{
    const auto player_behavior = player_->GetNextBehavior();
    if (player_behavior == BehaviorPattern::DEFENSE)
    {
        player_->DefenseProcess();
    }
    // 敵とは一体ずつ戦うと仮定する
    const auto enemy_behavior = enemies_.at(0)->GetNextBehavior();
    if (enemy_behavior == BehaviorPattern::DEFENSE)
    {
        enemies_.at(0)->DefenseProcess();
    }
}




void CharacterManager::Create()
{
	if (chara_manager_)
	{
		return;
	}
	chara_manager_ = new CharacterManager;
}


void CharacterManager::Destroy()
{
	delete chara_manager_;
}

void CharacterManager::Update()
{
    // 敵とは一体ずつ戦うとする
    if (!player_ || enemies_.empty() || !enemies_.at(0))
    {
        assert(false);
        printf("キャラデータがありません\n");
        return;
    }
    // 防御を選択した場合は、先に防御力を上げておく
    DefenseProcess();
    
    // 防御以外の行動を反映(プレイヤーの方が先に攻撃)
    // 攻撃を受ける側は先に状態が反映される
    bool death = false;
    // プレイヤーのターン
    CharaActionOnTurn(player_, enemies_.at(0), death);
    if (death)
    {
        game_manager::SetGameState(GameState::JUST_END);
        return;
    }
    // 敵のターン
    CharaActionOnTurn(enemies_.at(0), player_, death);
    if (death)
    {
        // 死んだ敵は削除
        enemies_.erase(enemies_.begin());
        game_manager::SetGameState(GameState::JUST_END);
        return;
    }
    TurnEndProcess();
}
// 状態異常の反映と行動をする
void CharacterManager::CharaActionOnTurn(const std::shared_ptr<CharaBase>& ATTACKER, const std::shared_ptr<CharaBase>& TARGET, bool& death)
{
    TARGET->ReflectState();
    if (TARGET->IsDead())
    {
        death = true;
        return;
    }
    ATTACKER->Act(TARGET);
    if (TARGET->IsDead())
    {
        death = true;
        return;
    }
}

void CharacterManager::TurnEndProcess()
{
    player_->TurnEndProcess();
    for (const auto& enemy : enemies_)
    {
        enemy->TurnEndProcess();
    }
}

void CharacterManager::SetChoiceToPc(const BehaviorPattern behavior) const
{
    if (!player_)
    {
        assert(false);
        printf("プレイヤーデータがありません\n");
        return;
    }
    player_->Setbehavior(behavior);
}



namespace character
{
void SetChoiceAction(const BehaviorPattern behavior)
{
    const auto chara_manager = CharacterManager::GetCharacterManager();
    if (!chara_manager)
    {
        assert(false);
        printf("chara_managerがありません\n");
        return;
    }
    chara_manager->SetChoiceToPc(behavior);
}
void Update()
{
    auto chara_manager = CharacterManager::GetCharacterManager();
    if (!chara_manager)
    {
        assert(false);
        printf("chara_managerがありません\n");
        return;
    }
    chara_manager->Update();
}

void Initialize()
{
    auto chara_manager = CharacterManager::GetCharacterManager();
    if (!chara_manager)
    {
        assert(false);
        printf("chara_managerがありません\n");
        return;
    }
    chara_manager->Initialize();
}

}

