#pragma once
#include "../Math/Transform.h"
#include "../Renderer/Model.h"

namespace viper {
	class Actor {
	public:
		Actor() = default;
		Actor(Transform transform, Model* model) : m_transform(transform), m_model{ model } {}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		Transform& GetTransform() { return m_transform; }
	protected:
		Transform m_transform{ {0, 0}, 0, 1 };
		Model* m_model;
	};
}