#include "Player.h"
//#include "engine.h"
#include "Input/InputSystem.h"

void Player::Update(float dt) {
	float speed = 150.0f;
	float rotationRate = 180;

	float rotate = 0;
	if (viper::GetEngine.GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate -= 1;
	if (viper::GetEngine.GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate += 1;
	m_transform.rotation += (rotate * rotationRate) * dt;

	float thrust = 0;
	if (input->GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	if (input->GetKeyDown(SDL_SCANCODE_S)) thrust = 1;

	vec2 direction{ 0, 0 };
	vec2 force = direction.Rotate(viper::math::degToRad(m_transform.rotation)) * thrust * speed;
	velocity += force * dt;

	Actor::Update(dt);
}