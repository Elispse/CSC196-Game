#include "Actor.h"

void Actor::Update(float dt)
{

}

void Actor::Draw(Jackster::Renderer& renderer)
{
	m_model.Draw(renderer, m_transform);
}
