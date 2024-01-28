#pragma once

constexpr auto pow(auto const base, auto const exponent) -> decltype(base)
{
    if (exponent == 0)
    {
        return 1;
    }

    return base * (exponent - 1 ? pow(base, exponent - 1) : 1);
}
