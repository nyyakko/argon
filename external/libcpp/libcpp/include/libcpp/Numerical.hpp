#pragma once

#include <stddef.h>

constexpr size_t number_size(auto const value)
{
    return 1 + ((value / 10) ? number_size(value / 10) : 0);
}

template <class T>
constexpr T reverse_number(T const value)
{
    auto reversed = value % 10;

    for ([[maybe_unused]] auto _ = 0zu; _ != number_size(value) - 1; _ += 1)
        // cppcheck-suppress useStlAlgorithm
        reversed *= 10;

    return reversed + ((value / 10) ? reverse_number(value / 10) : 0);
}

