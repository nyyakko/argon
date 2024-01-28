#pragma once

template <class T, class U>
struct IsSame
{
    auto static constexpr value = false;
};

template <class T>
struct IsSame<T, T>
{
    auto static constexpr value = true;
};

template <class T>
struct Decay
{
    using type = __decay(T);
};
