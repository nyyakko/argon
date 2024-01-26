#pragma once

#include <stddef.h>

namespace libc {

constexpr auto strlen(auto const* string)
{
    auto length = 0u;

    while (string[length] != '\0')
        length++;

    return length;
}

}
