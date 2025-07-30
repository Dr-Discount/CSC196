#include "SpaceGame.h"
#include "Game/Player.h"
#include "Game/Enemy.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Core/Random.h"
#include "Engine.h"
#include "Game/GameData.h"

bool SpaceGame::Initialize() {
	m_scene = std::make_unique<viper::Scene>();

	return true;
}

void SpaceGame::Update(float dt) {
    switch (m_gameState) {
    case SpaceGame::GameState::Initializee:
        m_gameState = GameState::Title;
        break;
    case SpaceGame::GameState::Title:
        if (viper::GetEngine().GetInputSystem().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::StartGame;
        }
        break;
    case SpaceGame::GameState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_gameState = GameState::StartRound;
        break;
    case SpaceGame::GameState::StartRound: {
        std::shared_ptr<viper::Model> playerM = std::make_shared < viper::Model>(GameData::playerPoints, vec3{ 0, 0, 255 });

        viper::Transform transform{ vec2{600 , 512}, 0, 5 };
        std::unique_ptr<Player> player = std::make_unique<Player>(transform, playerM);
        player->damping = 0.5f;
        player->name = "Player";
        player->tag = "Player";

        m_scene->AddActor(std::move(player));
        m_gameState = GameState::Game;
    }
        break;
    case SpaceGame::GameState::Game:
        m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0.0f) {
            m_enemySpawnTimer = 4;

            std::shared_ptr<viper::Model> enemyModel = std::make_shared < viper::Model>(GameData::enemyPoints, vec3{ 255, 255, 255 });
            viper::Transform transform{ vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 }, 0, 7 };
            std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
            enemy->damping = 1.0f;
            enemy->speed = (viper::random::getRandomFloat() * 500) + 300;
            enemy->tag = "enemy";
            m_scene->AddActor(std::move(enemy));
        }
	    m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
        break;
    case SpaceGame::GameState::PlayerDead:
        m_lives--;
        if (m_lives == 0) m_gameState = GameState::GameOver;
        else m_gameState = GameState::StartRound;
        break;
    case SpaceGame::GameState::GameOver:
        break;
    default:
        break;
    }

}

void SpaceGame::Draw() {
    m_scene->Draw(viper::GetEngine().GetRenderer());
}

void SpaceGame::Shutdown() {
	m_scene.reset();
}