#include <iostream>
#include "Core/core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include <vector>
#include "Input/InputSystem.h"



class Star {
public:
    Star(const Jackster::vec2& pos, const Jackster::vec2& vel) :
        m_pos{ pos },
        m_vel{ vel }
    {}

    void Update(int width, int height) {
        m_pos += m_vel;
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

    Jackster::Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("CSC196", 800, 600);

    Jackster::InputSystem inputSystem;
    inputSystem.Initialize();


    std::vector < Jackster::vec2> points{ {-10, 0}, { 0, -10 }, { 10, 0 }, {-10, 0} };
    Jackster::Model model{ points };

    std::vector<Star> stars;
    for (int i = 0; i < 1000; i++)
    {
        Jackster::vec2 pos(Jackster::Vector2(Jackster::random(renderer.GetWidth()), Jackster::random(renderer.GetHeight())));
        Jackster::vec2 vel(Jackster::randomf(1, 4), 0.0f);

        stars.push_back(Star(pos, vel));
    }

    // Main game loop
    bool quit = false;
    while (!quit)
    {
        inputSystem.Update();
        if (inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) 
        {
            quit = true;
        }

        if (inputSystem.GetMouseButtonDown(0) || inputSystem.GetMouseButtonDown(1) || inputSystem.GetMouseButtonDown(2)) {
            std::cout << "Mouse Pressed ";
            std::cout << inputSystem.GetMousePosition().x << " " << inputSystem.GetMousePosition().y << " " << std::endl;
        }

        renderer.setColor(0, 0, 0, 0);
        renderer.BeginFrame();
        // draw
        Jackster::vec2 vel(1.0f, 0.3f);

        for (auto& star : stars)
        {
            star.Update(renderer.GetWidth(), renderer.GetHeight());

            //renderer.setColor(Jackster::random(1, 254), 0, 0, 255);
            renderer.setColor(Jackster::random(1, 255),Jackster::random(1, 255), 255, 255);
            //renderer.drawPoint(star.m_pos.x, star.m_pos.y);
            star.Draw(renderer);
        }

        model.Draw(renderer, {400, 300}, 5.0f);

        renderer.EndFrame();
    }
    return 0;
}