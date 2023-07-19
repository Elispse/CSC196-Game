#include "Player.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Weapon.h"

void Player::Update(float dt)
{
    Actor::Update(dt);

    // movement
    float rotate = 0;
    if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
    m_transform.rotation += rotate * m_turnRate * Jackster::g_time.getDeltaTime();

    float thrust = 0;
    if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

    Jackster::Vector2 forward = Jackster::vec2(0, -1).Rotate(m_transform.rotation);
    m_transform.position += forward * m_speed * thrust * Jackster::g_time.getDeltaTime();
    m_transform.position.x = Jackster::Wrap(m_transform.position.x, (float)Jackster::g_renderer.GetWidth());
    m_transform.position.y = Jackster::Wrap(m_transform.position.y, (float)Jackster::g_renderer.GetHeight());

    // fire weapon
    if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
        !Jackster::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
    {
        // Create Weapon
        Jackster::Transform transform{ m_transform.position, m_transform.rotation};
        std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform, m_model);
        m_scene->Add(std::move(weapon)); 
    }
}