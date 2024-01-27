#pragma once

#include <stddef.h>

constexpr auto strlen(auto const* string)
{
    auto length = 0u;

    while (string[length] != '\0')
        length++;

    return length;
}

constexpr bool strcmp(char const* lhs, char const* rhs)
{
    auto const lhsSize = strlen(lhs);
    auto const rhsSize = strlen(rhs);
    auto const size    = lhsSize > rhsSize ? rhsSize : lhsSize;

    for (auto index = 0u; index <= size; index += 1)
    {
        if (lhs[index] != rhs[index]) return false;
    }

    return true;
}

constexpr auto memset(auto* destination, auto const byte, size_t const count)
{
    for (auto index = 0u; index != count; index += 1)
    {
        destination[index] = byte;
    }
}

constexpr auto memcpy(auto* destination, auto const* source, size_t count)
{
    for (auto index = 0zu; index != count; index += 1)
    {
        destination[index] = source[index];
    }
}

// https://opensource.apple.com/source/network_cmds/network_cmds-481.20.1/unbound/compat/memmove.c.auto.html
constexpr auto memmove(auto* destination, auto const* source, size_t count)
{
    if (destination == source || source == 0)
    {
        return;
    }

    if (destination > source && static_cast<size_t>(destination - source) < count)
    {
        for (auto index = count - 1; index != 0; index -= 1)
            destination[index] = source[index];
    }
    else if (destination < source && static_cast<size_t>(source - destination) < count)
    {
        for (auto index = 0zu; index != count; index += 1)
            destination[index] = source[index];
    }
}

