#include "Renderer.h"
#include "Model.h"

namespace viper {
	void Model::Draw(class Renderer& renderer, const vec2& position, float rotation, float scale) {
		if (m_points.empty()) return;

		renderer.SetColor(m_color.r, m_color.g, m_color.b);

		for (int i = 0; i < m_points.size() - 1; ++i) {
			const vec2& p1 = m_points[i].Rotate(math::degToRad(rotation)) * scale + position;
			const vec2& p2 = m_points[i + 1].Rotate(math::degToRad(rotation)) * scale + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
	void Model::Draw(class Renderer& renderer, const Transform& transform) {
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}
}