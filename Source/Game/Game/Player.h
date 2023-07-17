#pragma once
#include "Framework/Actor.h"

class Player : public Actor
{
public:
	Player(float speed, float turnrate, const Jackster::Transform& transform, const Jackster::Model& model) :
		Actor{ transform, model },
		m_speed{speed},
		m_turnRate{m_turnRate}
	{}

	void Update(float dt) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
};

