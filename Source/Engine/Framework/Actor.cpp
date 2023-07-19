#include "Actor.h"
namespace Jackster
{
	void Actor::Update(float dt)
	{
		if (m_lifespan != -1.0f)
		{
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}
	}

	void Actor::Draw(Jackster::Renderer& renderer)
	{
		m_model.Draw(renderer, m_transform);
	}
}
