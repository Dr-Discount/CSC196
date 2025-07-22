#pragma once
#include "../Math/Transform.h"
#include "../Renderer/Model.h"
#include <memory>
#include <string>

namespace viper {
	class Actor {
	public:
		std::string name;
		std::string tag;

		vec2 velocity{ 0, 0 };

	public:
		Actor() = default;
		Actor(Transform transform, class std::shared_ptr<Model> model) : m_transform(transform), m_model{ model } {}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		Transform& GetTransform() { return m_transform; }
	protected:
		Transform m_transform{ {0, 0}, 0, 1 };
		std::shared_ptr<Model> m_model;
	};
}