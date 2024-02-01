#pragma once

#include "TypeTraits.hpp"

template <class T, class U>
concept Same = IsSame<T, U>::value;

template <class T>
concept ArrayConcept = requires (T value)
{
    value.data();
    value.begin();
    value.end();
    value.size();

    { value[0] = typename T::type_t{} } -> Same<typename AddReference<typename T::type_t>::type>;
};

