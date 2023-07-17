#include "Player.h"
#include "Input//InputSystem.h"
#include "Renderer/Renderer.h"

void Player::Update(float dt)
{
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

    /*Jackster::vec2 direction;
    if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
    if (inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
    if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
    if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

    position += direction * speed * Jackster::g_time.getDeltaTime();

    if (inputSystem.GetMouseButtonDown(0) || inputSystem.GetMouseButtonDown(1) || inputSystem.GetMouseButtonDown(2)) {
        std::cout << "mouse pressed" << std::endl;
        Jackster::Vector2 vect = inputSystem.GetMousePosition();
        std::cout << "X-Coord:" << vect.x << "Y-Coord:" << vect.y << std::endl;
    }*/
}