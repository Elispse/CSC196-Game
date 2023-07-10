#include <iostream>
#include "Core/core.h"
#include "Renderer/Renderer.h"
#include <vector>


class Star {
public:
    Star(const Jackster::Vector2& pos, const Jackster::Vector2& vel) :
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

    std::vector<Star> stars;
    for (int i = 0; i < 1000; i++)
    {
        Jackster::vec2 pos(Jackster::Vector2(Jackster::random(renderer.GetWidth()), Jackster::random(renderer.GetHeight())));
        Jackster::vec2 vel(Jackster::randomf(1, 4), 0.0f);

        stars.push_back(Star(pos, vel));
    }

    while (true)
    {
        renderer.setColor(0, 0, 0, 0);
        renderer.BeginFrame();
        // draw
        Jackster::vec2 vel(1.0f, 0.3f);

        for (auto& star : stars)
        {
            star.Update(renderer.GetWidth(), renderer.GetHeight());

            //renderer.setColor(Jackster::random(1, 254), 0, 0, 255);
            renderer.setColor(Jackster::random(1, 255),Jackster::random(), 255, 255);
            //renderer.drawPoint(star.m_pos.x, star.m_pos.y);
            star.Draw(renderer);
        }

        renderer.EndFrame();

        /*for (int i = 0; i < 1000; i++)
        {

            renderer.setColor(Jackster::random(1, 254), 0, 0, 255);
            renderer.drawPoint(Jackster::random(renderer.GetWidth()), Jackster::random(renderer.GetHeight()));


            renderer.EndFrame();
        }*/
    }
    

    /*Jackster::g_MemoryTracker.displayInfo();
    int* p = new int;
    Jackster::g_MemoryTracker.displayInfo();
    delete p;
    Jackster::g_MemoryTracker.displayInfo();

    Jackster::Time timer;
    for (int i = 0; i < 10000000; i++) {}
    std::cout << timer.GetElapsedSeconds() << std::endl;*/



   /* auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000000; i++) {}
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << (end - start).count() << std::endl;

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();*/


   /* std::cout << Jackster::getFilePath() << std::endl;
    Jackster::setFilePath("Assets");
    std::cout << Jackster::getFilePath() << std::endl;
    size_t size;
    Jackster::getFileSize("game.txt", size);
    std::cout << size << std::endl;

    std::string s;
    Jackster::readFile("game.txt", s);
    std::cout << s << std::endl;

    Jackster::seedRandom((unsigned int)time(nullptr));
    for (int i = 0; i < 10; i++) {
        std::cout << Jackster::random(5, 10) << std::endl;

        std::cout << Jackster::getFilePath() << std::endl;
    }
        Jackster::seedRandom((unsigned int)time(nullptr));
        for (int i = 0; i < 10; i++) {
            std::cout << Jackster::random(5, 10) << std::endl;
        }*/
}