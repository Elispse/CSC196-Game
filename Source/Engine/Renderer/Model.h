#pragma once
#include "Core/core.h"
#include "Renderer.h"


namespace Jackster {

	class Model
	{
	public:
		Model() = default;
		Model(std::vector<vec2>& points) : m_points{ points } {};

		bool Load(const std::string& filename);
		void Draw(Renderer& renderer, const vec2 position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& transform);
		float getRadius();
		
	private:
		std::vector<vec2> m_points;
		Color m_color;
		float m_radius = 0;
	};

}