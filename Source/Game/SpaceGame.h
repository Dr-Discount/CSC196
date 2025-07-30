#pragma once
#include "Framework/Game.h"

class SpaceGame : viper::Game {
public:
	enum GameState {
		Initializee,
		Title,
		StartGame,
		StartRound,
		Game,
		PlayerDead,
		GameOver
	};

public:
	SpaceGame() = default;

	bool Initialize() override;
	void Update(float dt) override;
	void Draw() override;
	void Shutdown() override;
private:
	GameState m_gameState = GameState::Initializee;
	float m_enemySpawnTimer = 0.0f;
};