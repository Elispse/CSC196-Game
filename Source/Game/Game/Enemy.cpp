#include "Enemy.h"
#include "Player.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Weapon.h"
#include "Audio/AudioSystem.h"

void Enemy::Update(float dt)
{
    Actor::Update(dt);

    auto* player = m_scene->getActor<Player>();
    if (player)
    {
        Jackster::Vector2 direction = player->m_transform.position - m_transform.position;
        m_transform.rotation = direction.angle() + Jackster::halfPi;
    }

    Jackster::Vector2 forward = Jackster::vec2(0, -1).Rotate(m_transform.rotation);
    m_transform.position += forward * m_speed * Jackster::g_time.getDeltaTime();
    m_transform.position.x = Jackster::Wrap(m_transform.position.x, (float)Jackster::g_renderer.GetWidth());
    m_transform.position.y = Jackster::Wrap(m_transform.position.y, (float)Jackster::g_renderer.GetHeight());

    m_fireTimer -= dt;
    if (m_fireTimer <= 0)
    {
        m_fireTimer = m_fireRate;
        // Create Weapon
        Jackster::Transform transform{ m_transform.position, m_transform.rotation};
        std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform, m_model);
        m_scene->Add(std::move(weapon));

        Jackster::g_audioSystem.Initialize();
        Jackster::g_audioSystem.AddAudio("shoot", "Laser_Shoot.wav");
        Jackster::g_audioSystem.PlayOneShot("shoot");
        std::cout << "fire";
    }
    
}