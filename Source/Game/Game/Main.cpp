#include "Core/core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Actor.h"
#include "Player.h"
#include "Enemy.h"
#include <thread>
#include <vector>
#include <iostream>

class Star {
public:
    Star(const Jackster::vec2& pos, const Jackster::vec2& vel) :
        m_pos{ pos },
        m_vel{ vel }
    {}

    void Update(int width, int height) {
        m_pos += m_vel * Jackster::g_time.getDeltaTime();
        if (m_pos.x >= width) m_pos.x = 0;
        if (m_pos.y >= height) m_pos.y = 0;
    }

    void Draw(Jackster::Renderer& renderer) {
        renderer.drawPoint(m_pos.x, m_pos.y);
    }
public:
    Jackster::vec2 m_pos;
    Jackster::vec2 m_vel;
};

int main(int argc, char* argv[]) {


    int m1 = Jackster::Max(4.0f, 3.0f);
    int m2 = Jackster::Max(4, 3);

    Jackster::seedRandom((unsigned) time(nullptr));
    Jackster::setFilePath("assets");

    Jackster::g_renderer.Initialize();
    Jackster::g_renderer.CreateWindow("CSC196", 800, 600);

    Jackster::g_inputSystem.Initialize();
    
    Jackster::g_audioSystem.Initialize();
    Jackster::g_audioSystem.AddAudio("hit", "Hit_Hurt.wav");
    Jackster::g_audioSystem.AddAudio("death", "Explosion.wav");
    Jackster::g_audioSystem.AddAudio("shoot", "Laser_Shoot.wav");

    Jackster::Model model;
    model.Load("Ship.txt");

    Jackster::vec2 v{5, 5};
    v.normalize();


    std::vector<Star> stars;
    for (int i = 0; i < 1000; i++)
    {
        Jackster::vec2 pos(Jackster::Vector2(Jackster::random(Jackster::g_renderer.GetWidth()), Jackster::random(Jackster::g_renderer.GetHeight())));
        Jackster::vec2 vel(Jackster::randomf(1, 4), 70.0f);

        stars.push_back(Star(pos, vel));
    }

    Jackster::Transform transform{{400, 300}, 0, 3};
    constexpr float turnRate = Jackster::degreesToRadians(180);
    Jackster::vec2 position{400, 300};
    float speed = 150;
    float scale = 5;

    Player player{200, Jackster::pi, { {400, 300}, 0, 6}, model };
    Enemy enemy{200, Jackster::pi, { {400, 300}, 0, 6}, model };

    std::vector<Enemy> enemies;
    for (int i = 0; i < 100; i++) 
    {
        Enemy enemy{ 300, Jackster::pi, { {400, 300}, Jackster::randomf(Jackster::pi2), 6}, model};  
        enemies.push_back(enemy);
    }


    // Main game loop
    bool quit = false;
    while (!quit)
    {
        Jackster::g_time.tick();
        Jackster::g_inputSystem.Update();
        Jackster::g_audioSystem.Update();
        if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) 
        {
            quit = true;
        }

        Jackster::vec2 direction;
        if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
        if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
        if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
        if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

        position += direction * speed * Jackster::g_time.getDeltaTime();

        if (Jackster::g_inputSystem.GetMouseButtonDown(0) || Jackster::g_inputSystem.GetMouseButtonDown(1) || Jackster::g_inputSystem.GetMouseButtonDown(2)) {
            std::cout << "mouse pressed" << std::endl;
            Jackster::Vector2 vect = Jackster::g_inputSystem.GetMousePosition();
            std::cout << "X-Coord:" << vect.x << "Y-Coord:" << vect.y << std::endl;
        }

        if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
        {
            Jackster::g_audioSystem.PlayOneShot("shoot");
        }

        player.Update(Jackster::g_time.getDeltaTime());
        for (auto& enemy : enemies) enemy.Update(Jackster::g_time.getDeltaTime());
        
        // draw
        Jackster::vec2 vel(1.0f, 0.3f);
        Jackster::g_renderer.setColor(0, 0, 0, 0);
        Jackster::g_renderer.BeginFrame();

        for (auto& star : stars)
        {
            star.Update(Jackster::g_renderer.GetWidth(), Jackster::g_renderer.GetHeight());

            star.m_pos.x + 1;
            star.m_pos.y += 0.3f;

            if (star.m_pos.x >= Jackster::g_renderer.GetWidth()) star.m_pos.x = 0;
            if (star.m_pos.y >= Jackster::g_renderer.GetHeight()) star.m_pos.y = 0;

            Jackster::g_renderer.setColor(Jackster::random(256), 255, 255, 255);
            Jackster::g_renderer.setColor(Jackster::random(256), Jackster::random(256), Jackster::random(256), 255);//draw
            Jackster::g_renderer.drawPoint(star.m_pos.x, star.m_pos.y);
        }
        player.Draw(Jackster::g_renderer);
        for (auto& enemy : enemies) enemy.Draw(Jackster::g_renderer);
        
        Jackster::g_renderer.EndFrame();
    }
    return 0;
}