#pragma once

#include <stddef.h>

namespace libc {

constexpr auto memset(auto* destination, auto byte, size_t count)
{
    for (auto index = 0u; index != count; index += 1)
    {
        destination[index] = byte;
    }
}

}
