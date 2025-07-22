#include "SpaceGame.h"
#include "Game/Player.h"
#include "Game/Enemy.h"
#include "Game/Scene.h"

bool SpaceGame::Initialize() {
	m_scene = std::make_unique<viper::Scene>();
}

void SpaceGame::Update(float dt) {
	
}
