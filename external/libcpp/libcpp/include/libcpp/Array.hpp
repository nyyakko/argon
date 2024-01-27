#pragma once

#include <stddef.h>

template <class T, size_t Size>
struct Array
{
    T values_m[Size] {};
    size_t size_m {};

    constexpr auto begin() const { return &values_m[0]; }
    constexpr auto end() const { return &values_m[Size]; }
    constexpr auto size() const { return size_m; }
};

