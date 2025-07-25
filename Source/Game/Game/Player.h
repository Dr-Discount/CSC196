#pragma once
#include "Game/Actor.h"
#include "Renderer/Model.h"

class Player : public viper::Actor {
public:
	Player() = default;
	Player(viper::Transform transform, std::shared_ptr<viper::Model> model)
		: Actor{ transform, model } {}

	void Update(float dt) override;

private:

};
