#include "Core/core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Enemy.h"

#include <thread>
#include <vector>
#include <iostream>
#include <memory>

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

    Jackster::MemoryTracker::Initialize();
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
        Jackster::vec2 vel(Jackster::randomf(1, 4), 0.0f);

        stars.push_back(Star(pos, vel));
    }

    Jackster::Transform transform{{400, 300}, 0, 3};
    constexpr float turnRate = Jackster::degreesToRadians(180);
    Jackster::vec2 position{400, 300};
    float speed = 150;
    float scale = 5;

    Jackster::Scene scene;

    std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, Jackster::pi, Jackster::Transform{ {400, 300}, 0, 6 }, model);
    scene.Add(std::move(player));
    for (int i = 0; i < 1; i++) 
    {
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(150.0f, Jackster::pi, Jackster::Transform{ {400, 300}, Jackster::randomf(Jackster::pi2), 6 }, model);
        scene.Add(std::move(enemy));
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

        if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
            !Jackster::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
        {
            Jackster::g_audioSystem.PlayOneShot("shoot");
        }

        //update Game
        scene.Update(Jackster::g_time.getDeltaTime());

        Jackster::vec2 direction;
        position += direction * speed * Jackster::g_time.getDeltaTime();


        // draw
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

        scene.Draw(Jackster::g_renderer);

        Jackster::g_renderer.EndFrame();
    }

    stars.clear();
    scene.RemoveAll();

    return 0;
}