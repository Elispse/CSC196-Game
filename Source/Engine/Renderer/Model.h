#pragma once
#include "Core/core.h"
#include "Renderer.h"


namespace Jackster {

	class Model
	{
	public:
		Model() = default;
		Model(std::vector<vec2>& points) : m_points{ points } {};

		void Draw(Renderer& renderer, const vec2 position, float scale);
	private:
		std::vector<vec2> m_points;
	};

}