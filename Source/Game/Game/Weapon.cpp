#include "Weapon.h"

void Weapon::Update(float dt)
{
    Actor::Update(dt);
    
    Jackster::Vector2 forward = Jackster::vec2(0, -1).Rotate(m_transform.rotation);
    m_transform.position += forward * m_speed * Jackster::g_time.getDeltaTime();
    m_transform.position.x = Jackster::Wrap(m_transform.position.x, (float)Jackster::g_renderer.GetWidth());
    m_transform.position.y = Jackster::Wrap(m_transform.position.y, (float)Jackster::g_renderer.GetHeight());
}