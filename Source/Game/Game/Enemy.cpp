#include "Enemy.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Framework/Game.h"
#include "Player.h"
#include "Rocket.h"
#include "GameData.h"
#include "Math/Vector3.h"

void Enemy::Update(float dt) {
	Player* player = scene->GetActorByName<Player>("Player");
	if (player) {
		vec2 direction{ 0, 0 };
		direction = player->transform.position - transform.position;
		direction = direction.Normalized();
		transform.rotation = viper::math::radToDeg(direction.Angle());
	}

	vec2 force = vec2{ 1, 0}.Rotate(viper::math::degToRad(transform.rotation)) * speed;
	velocity += force * dt;

	transform.position.x = viper::math::wrap(transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	transform.position.y = viper::math::wrap(transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());
	
	fireTimer -= dt;
	if ( fireTimer <= 0) {
		fireTimer = fireTime;
		std::shared_ptr<viper::Model> rocketM = std::make_shared < viper::Model>(GameData::playerPoints, vec3{ 255, 0, 0 });
		viper::Transform transform{ this->transform.position, this->transform.rotation, 2 };
		auto rocket = std::make_unique<Rocket>(transform, rocketM);
		rocket->damping = 0.5f;
		rocket->speed = 500.0f;
		rocket->lifespan = 1.5f;
		rocket->name = "rocket";
		rocket->tag = "rocket";
		scene->AddActor(std::move(rocket));
	}

	Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other) {
	if (tag != other->tag) {
		destroyed = true;
		scene->GetGame()->AddPoints(10);
	}
}