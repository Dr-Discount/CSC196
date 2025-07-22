#pragma once
#include "Game/Actor.h"
#include "Renderer/Model.h"

class Enemy : public viper::Actor {
public:
	Enemy() = default;
	Enemy(viper::Transform transform, std::shared_ptr<viper::Model> model)
		: Actor{ transform, model } {
	}

	void Update(float dt) override;

private:

};