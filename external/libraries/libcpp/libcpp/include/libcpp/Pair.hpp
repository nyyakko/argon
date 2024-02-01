#pragma once

template <class T, class U>
struct Pair
{
    T first {};
    U second {};

    constexpr auto operator==(Pair const& rhs) const { return first == rhs.first && second == rhs.second; }
    constexpr auto operator!=(Pair const& rhs) const { return !(*this == rhs); }
    constexpr operator bool() const { return first && second; }
};

