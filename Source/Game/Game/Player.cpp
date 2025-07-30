#include "Player.h"
#include "engine.h"
#include "Math/Math.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include <SDL3/SDL_scancode.h>

void Player::Update(float dt) {
	float rotate = 0;
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_A)) rotate -= 1;
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_D)) rotate += 1;
	
	transform.rotation += (rotate * rotationRate) * dt;
	
	float thrust = 0;
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

	vec2 direction{ 1, 0 };
	vec2 force = direction.Rotate(viper::math::degToRad(transform.rotation)) * thrust * speed;
	velocity += force * dt;

	transform.position.x = viper::math::wrap(transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	transform.position.y = viper::math::wrap(transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());



	Actor::Update(dt);
}