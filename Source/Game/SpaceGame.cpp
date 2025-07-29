#include "SpaceGame.h"
#include "Game/Player.h"
#include "Game/Enemy.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Engine.h"



bool SpaceGame::Initialize() {
    std::vector<vec2> arrowPoints = {
    {4, 0},
    {-3, 3},
    {-2, 0},
    {-3, -3},
    {4, 0}
    };

	m_scene = std::make_unique<viper::Scene>();

    std::shared_ptr<viper::Model> playerM = std::make_shared < viper::Model>(arrowPoints, vec3{ 0, 0, 255});

    viper::Transform transform{ vec2{600 , 512}, 0, 5 };
    std::unique_ptr<Player> player = std::make_unique<Player>(transform, playerM);
    player->damping = 0.3f;
	player->name = "Player";

    m_scene->AddActor(std::move(player));
	
    std::shared_ptr<viper::Model> enemyModel = std::make_shared < viper::Model>(arrowPoints, vec3{ 255, 255, 255 });
    for (int i = 0; i < 10; i++) {
        viper::Transform transform{ vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 }, 0, 10 };
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
        m_scene->AddActor(std::move(enemy));
    }

	return true;
}

void SpaceGame::Update() {
	m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw() {
    m_scene->Draw(viper::GetEngine().GetRenderer());
}

void SpaceGame::Shutdown() {
	m_scene.reset();
}