#pragma once
#include "Framework/Actor.h"

class Weapon : public Jackster::Actor
{
public:
	Weapon(float speed, const Jackster::Transform& transform, const Jackster::Model& model) :
		Actor{ transform, model },
		m_speed{ speed }
	{
		m_lifespan = 2.0f;
	}

	void Update(float dt) override;

private:
	float m_speed = 0;
};

