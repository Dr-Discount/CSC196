#include "Enemy.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"

void Enemy::Update(float dt) {
	Actor* player = scene->GetActorByName("Player");
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

	Actor::Update(dt);
}