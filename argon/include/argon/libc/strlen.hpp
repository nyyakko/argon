#pragma once

#include <stddef.h>

namespace libc {

constexpr auto strlen(auto const* string) noexcept
{
    auto length = 0zu;

    while (string[length] != '\0')
        length++;

    return length;
}

}
