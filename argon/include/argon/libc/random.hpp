#pragma once

namespace libc {

    namespace {

    static unsigned long int next = 1;

    }

    inline int rand(void)
    {
        next = next * 1103515245 + 12345;
        return (next / 65536) % 32768;
    }

    inline void srand(unsigned int seed)
    {
        next = seed;
    }

}
