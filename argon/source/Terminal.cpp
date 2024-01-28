#include "Terminal.hpp"

#include <libcpp/Iota.hpp>
#include <libcpp/Numerical.hpp>
#include <libc/math.hpp>

void Terminal::put(char const data, VGAColor const foreground, VGAColor const background)
{
    VGA::put_entry(VGAEntry(data, foreground, background));
}

void Terminal::put(StringView const data, VGAColor const foreground, VGAColor const background)
{
    for (auto index = 0lu; index < data.size(); index++)
    {
        put(data.data()[index], foreground, background);
    }
}

void Terminal::putf(StringView const format, ...)
{
    char const* variadic = reinterpret_cast<char const*>(&format) + sizeof(StringView);

    for (auto index = 0zu; index < format.size(); index += 1)
    {
        if (format.data()[index] != '%')
            Terminal::put(format.data()[index]);
        else
        {
            switch (format.data()[index += 1])
            {
            case 'd': {
                auto number = *reinterpret_cast<int const*>(variadic);

                for (auto exponent = number_size(number); exponent != 0; exponent -= 1)
                {
                    auto const power = pow(10, exponent - 1);
                    auto const digit = number / power;
                    Terminal::put(char('0' + digit));
                    number -= digit * power;
                }

                variadic += sizeof(int);
                break;
            }
            case 'v': {
                Terminal::put(*reinterpret_cast<StringView const*>(variadic));
                variadic += sizeof(StringView);
                break;
            }
            }
        }
    }
}

void Terminal::putln(StringView const data, VGAColor const foreground, VGAColor const background)
{
    put(data, foreground, background);
    put("\n"_sv, foreground, background);
}

