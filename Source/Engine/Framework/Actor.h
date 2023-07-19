#pragma once
#include <Core/core.h>
#include "Renderer/Model.h"

namespace Jackster
{
class Actor
{
	public:
		Actor() = default;
		Actor(const Jackster::Transform& transform, const Jackster::Model& model) :
			m_transform{ transform },
			m_model{ model }
		{}

		virtual void Update(float dt);
		virtual void Draw(Jackster::Renderer& renderer);

		class Scene* m_scene = nullptr;
		friend class Scene;

		Jackster::Transform m_transform;
	protected:
		bool m_destroyed = false;
		float m_lifespan = -1.0f;

		Jackster::Model m_model;
	};
}

