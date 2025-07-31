#pragma once
#include "Framework/Actor.h"
#include "Renderer/Model.h"

class Enemy : public viper::Actor {
public:
	float speed = 250.0f;
	float fireTime = 2.0f;
	float fireTimer = 3.0f;

	Enemy() = default;
	Enemy(viper::Transform transform, std::shared_ptr<viper::Model> model)
		: Actor{ transform, model } {
	}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:

};