#pragma once
#include "Framework/Actor.h"
#include "Renderer/Model.h"

class Player : public viper::Actor {
public:
	float speed = 500.0f;
	float rotationRate = 180.0f;

public:
	Player() = default;
	Player(viper::Transform transform, std::shared_ptr<viper::Model> model)
		: Actor{ transform, model } {}

	void Update(float dt) override;

private:

};
