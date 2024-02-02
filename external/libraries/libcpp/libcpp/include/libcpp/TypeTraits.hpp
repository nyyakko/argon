#pragma once

template <class T>
struct Decay
{
    using type = __decay(T);
};

template <class T>
struct AddReference
{
    using type = Decay<T>::type&;
};

template <class T, T Value>
struct IntegralConstant { auto static constexpr value = Value; };

using TrueType  = IntegralConstant<bool, true>;
using FalseType = IntegralConstant<bool, false>;

template <class T, class U>
struct IsSame : IntegralConstant<bool, false> { };

template <class T>
struct IsSame<T, T> : IntegralConstant<bool, true> { };

template <class T> static AddReference<T>::type declval();

namespace {

    template <class From, class To>
    static auto implicitly_convertible(int) -> decltype(
        void(declval<void(&)(To)>()(declval<From>())), TrueType{}
    );

    template <class, class>
    static auto implicitly_convertible(auto...) -> FalseType;
}

template <class From, class To>
struct IsConvertible :
    IntegralConstant<bool, decltype(implicitly_convertible<From, To>(0))::value>
{
};

template <class T>
struct IsIntegral : IntegralConstant<bool, 
    requires (T value, T* pointer, void(*func)(T))
    {
        reinterpret_cast<T>(value);
        func(0);
        pointer + value;
    }>
{};

template <class T>
struct IsFloatingPoint : IntegralConstant<bool,
    IsSame<float, typename Decay<T>::type>::value ||
    IsSame<double, typename Decay<T>::type>::value ||
    IsSame<long double, typename Decay<T>::type>::value>
{};

template <class T>
struct IsArithmetic : IntegralConstant<bool,
    IsIntegral<T>::value || IsFloatingPoint<T>::value
    >
{};

template <class T>
struct IsIterable : IntegralConstant<bool,
    requires (T value)
    {
        value.begin();
        value.end();
        value[0];
    }>
{};

