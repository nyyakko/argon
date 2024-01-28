#pragma once

#include <libc/math.hpp>
#include <libcpp/StringView.hpp>
#include <libcpp/TypeTraits.hpp>
#include <libcpp/Numerical.hpp>

#include "hardware/VGA.hpp"
#include "hardware/VGAColor.hpp"

class Terminal
{
public:
    Terminal()
    {
        VGA::initialize();
    }

public:
    static Terminal& initialize()
    {
        static Terminal the {};
        return the;
    }

    static void put(char const data, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK);
    static void put(StringView const data, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK);
    static void putln(StringView const data, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK);

    static void putf(StringView const format, auto first, auto&&... args)
    {
        for (auto index = 0zu; index != format.size(); index += 1)
        {
            if (auto const byte = format.data()[index]; byte != '%')
                Terminal::put(byte);
            else
            {
                using first_t = Decay<decltype(first)>::type;

                switch (format.data()[index += 1])
                {
                case 'd': {
                    if constexpr (IsConvertible<first_t, int>::value)
                    {
                        first_t value = first;

                        for (auto exponent = number_size(value); exponent != 0; exponent -= 1)
                        {
                            first_t const power = pow<first_t>(10, exponent - 1);
                            first_t const digit = value / power;
                            Terminal::put(char('0' + digit));
                            value -= digit * power;
                        }
                    }
                    break;
                }
                case 's': {
                    if constexpr (IsSame<first_t, StringView>::value || IsSame<first_t, char const*>::value)
                    {
                        Terminal::put(first);
                    }
                    break;
                }
                }

                putf(&format.data()[index + 1], args...);
                break;
            }
        }
    }

private:
    static void putf(StringView const format)
    {
        Terminal::put(format);
    }
};

