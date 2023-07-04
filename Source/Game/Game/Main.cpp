#include <iostream>
#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/memory.h"
#include "Core/Time.h"
#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Renderer/Renderer.h"

int main() {
    Jackster::g_MemoryTracker.displayInfo();
    int* p = new int;
    Jackster::g_MemoryTracker.displayInfo();
    delete p;
    Jackster::g_MemoryTracker.displayInfo();

    Jackster::Time timer;
    for (int i = 0; i < 10000000; i++) {}
    std::cout << timer.GetElapsedSeconds() << std::endl;



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