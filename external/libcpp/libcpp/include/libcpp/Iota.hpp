#pragma once

#include <stddef.h>

class Iota
{
    constexpr explicit Iota(size_t current): current_m(current) {}

public:
    constexpr Iota(size_t minimum, size_t maximum):
        minimum_m(minimum),
        maximum_m(maximum)
    {}

    constexpr auto begin() { return Iota(minimum_m); }
    constexpr auto end() { return Iota(maximum_m); }

    constexpr auto operator!=(auto const& lhs) const { return current_m != lhs.current_m; }

    constexpr auto operator*() { return current_m; }
    constexpr auto operator++() { return current_m += 1; }

private:
    size_t minimum_m {};
    size_t maximum_m {};
    size_t current_m {};
};

