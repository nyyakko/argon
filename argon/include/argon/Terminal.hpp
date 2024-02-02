#pragma once

#include <libc/math.hpp>
#include <libcpp/Numerical.hpp>
#include <libcpp/StringView.hpp>
#include <libcpp/TypeTraits.hpp>

#include "hardware/VGA.hpp"
#include "hardware/VGAColor.hpp"

class Terminal
{
    Pair<VGAColor, VGAColor> static constexpr DEFAULT_CURSOR_COLOR { VGAColor::LIGHT_GREY, VGAColor::BLACK };

    Terminal()
    {
        VGA::initialize();
    }

public:
    static Terminal& initialize()
    {
        static Terminal terminal {};
        return terminal;
    }

    static Terminal& the() { return Terminal::initialize(); }

    static void set_cursor_color(Pair<VGAColor, VGAColor> const color);
    static Pair<VGAColor, VGAColor> get_cursor_color();

    static void put(char const data, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK);
    static void put(StringView const data, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK);
    static void putln(StringView const data, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK);

    static void putf(StringView const format, auto&& first, auto&&... args)
    {
        for (auto index = 0zu; index != format.size(); index += 1)
        {
            if (auto const byte = format.data()[index]; byte != '{')
                Terminal::put(byte);
            else
            {
                using first_t = Decay<decltype(first)>::type;

                index += 1;

                if constexpr (IsConvertible<first_t, StringView>::value || IsSame<first_t, char>::value)
                {
                    Terminal::put(first);
                }
                else if constexpr (IsSame<first_t, bool>::value)
                {
                    if (first == true)
                        Terminal::put("true");
                    else
                        Terminal::put("false");
                }
                else if constexpr (IsIntegral<first_t>::value)
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
                // cppcheck-suppress constStatement
                else if constexpr (requires (first_t value) { value.first; value.second; })
                {
                    Terminal::putf("[{}, {}]", first.first, first.second);
                }
                else if constexpr (IsIterable<first_t>::value)
                {
                    Terminal::put("[");

                    for (StringView prefix = ""; auto&& value : first)
                    {
                        Terminal::put(prefix), Terminal::putf("{}", value), prefix = ", ";
                    }

                    Terminal::put("]");
                }
                else
                {
                    static_assert(false, "an invalid type was given to putf");
                }

                if (index + 1 < format.size())
                {
                    putf(&format.data()[index + 1], args...);
                }

                break;
            }
        }
    }

private:
    static void putf(StringView const format)
    {
        Terminal::put(format);
    }

    Pair<VGAColor, VGAColor> cursorColor_m { VGAColor::LIGHT_GREY, VGAColor::BLACK };
};

