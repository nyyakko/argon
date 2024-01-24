#pragma once

#include <stddef.h>

namespace libc {

constexpr auto memset(auto* destination, auto byte, size_t count)
{
    for (auto index = 0zu; index != count; index += 1)
    {
        destination[index] = byte;
    }
}

}
