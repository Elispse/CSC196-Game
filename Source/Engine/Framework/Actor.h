#pragma once
#include <Core/core.h>
#include "Renderer/Model.h"

class Actor
{
public:
	Actor() = default;
	Actor(const Jackster::Transform& transform, const Jackster::Model& model) :
		m_transform{ transform },
		m_model{ model }
	{}

	virtual void Update(float dt) = 0;
	virtual void Draw(Jackster::Renderer& renderer);

protected:
	Jackster::Transform m_transform;
	Jackster::Model m_model;
};

