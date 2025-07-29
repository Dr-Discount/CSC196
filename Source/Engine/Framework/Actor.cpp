#include "Actor.h"
#include "../Renderer/Renderer.h"

namespace viper {
	void Actor::Update(float dt) {
		transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt));
	}

	void Actor::Draw(Renderer& renderer) {
		m_model->Draw(renderer, transform);
	}
}