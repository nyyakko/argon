#pragma once

#include <stddef.h>

namespace libc {

constexpr auto memcpy(auto* destination, auto const* source, size_t count)
{
    for (auto index = 0zu; index != count; index += 1)
    {
        destination[index] = source[index];
    }
}

}
