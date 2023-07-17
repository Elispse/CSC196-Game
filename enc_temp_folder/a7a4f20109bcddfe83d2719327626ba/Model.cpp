#include "Model.h"
#include <sstream>

namespace Jackster {
	bool Model::Load(const std::string& filename)
	{
		std::string buffer;
		Jackster::readFile(filename, buffer);

		std::istringstream stream(buffer);

		std::string line;
		std::getline(stream, line);

		int numPoints = std::stoi(line);

		return true;
	}


	void Model::Draw(Renderer& renderer, const vec2 position, float scale)
	{
		if (m_points.empty()) return;

		for (int i = 0; i < m_points.size() - 1; i++)
		{
			vec2 p1 = (m_points[i] * scale) + position;
			vec2 p2 = (m_points[i + 1]* scale) + position;

			renderer.drawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
}
