#pragma once

#include <stddef.h>

template <class T, size_t Size>
struct Array
{
    T values_m[Size] {};

    using type_t = T;

    constexpr auto* data() { return &values_m[0]; }
    constexpr auto const* data() const { return &values_m[0]; }
    constexpr auto* begin() { return &values_m[0]; }
    constexpr auto const* begin() const { return &values_m[0]; }
    constexpr auto* end() { return &values_m[Size]; }
    constexpr auto const* end() const { return &values_m[Size]; }
    // cppcheck-suppress functionStatic
    constexpr auto size() { return Size; }
    // cppcheck-suppress functionStatic
    constexpr auto size() const { return Size; }

    constexpr auto& operator[](size_t index) { return values_m[index]; }
    constexpr auto const& operator[](size_t index) const { return values_m[index]; }
};

template <class T, class... U>
Array(T, U...) -> Array<T, 1 + sizeof...(U)>;

