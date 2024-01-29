#pragma once

#include <stdint.h>

namespace libc {

    namespace {

    static uint32_t next = 1;

    }

    inline int rand()
    {
        next = next * 1103515245 + 12345;
        return (next / 65536) % 32768;
    }

    inline void srand(uint32_t const seed)
    {
        next = seed;
    }

}
