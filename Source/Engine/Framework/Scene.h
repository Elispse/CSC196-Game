#pragma once

namespace Jackster 
{
	class Renderer;
	class Scene
	{
	public:
		Scene() = default;

		void Update(float dt);
		void Draw(Renderer& renderer);

	private:

	};
}

