#pragma once

namespace libc {

constexpr bool strcmp(char const* lhs, char const* rhs)
{
    auto const fnStrlen = [] (auto const* string) constexpr {
        auto length = 0u;

        while (string[length] != '\0')
            length++;

        return length;
    };

    auto const lhsSize = fnStrlen(lhs);
    auto const rhsSize = fnStrlen(rhs);
    auto const size    = lhsSize > rhsSize ? rhsSize : lhsSize;

    for (auto index = 0u; index <= size; index += 1)
    {
        if (lhs[index] != rhs[index]) return false;
    }

    return true;
}

}
