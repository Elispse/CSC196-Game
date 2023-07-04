#include "memory.h"
#include <iostream>

Jackster::MemoryTracker Jackster::g_MemoryTracker;

void* operator new (size_t size) {
    void* p = malloc(size);

    Jackster::g_MemoryTracker.Add(p, size);

    return p;
}

void operator delete (void* address, size_t size) {
    Jackster::g_MemoryTracker.Remove(address, size);
    free(address);
}

namespace Jackster {


    void MemoryTracker::Add(void* address, size_t size) {
        m_bytesAllocated += size;
        m_numAllocations++;
    }

    void MemoryTracker::Remove(void* address, size_t size) {
        m_bytesAllocated -= size;
        m_numAllocations--;
    }

    void MemoryTracker::displayInfo() {
        std::cout << "current bytes allocated: " << m_bytesAllocated << std::endl;
        std::cout << "current Num Allocated: " << m_numAllocations << std::endl;
    }
}