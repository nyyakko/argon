#include "Terminal.hpp"

#include <libcpp/Iota.hpp>
#include <libcpp/Numerical.hpp>

void Terminal::put(char data, VGAColor const foreground, VGAColor const background)
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

void Terminal::putf(StringView format, ...)
{
    char* variadic = reinterpret_cast<char*>(&format) + sizeof(StringView);

    for (auto index = 0zu; index < format.size(); index += 1)
    {
        if (format.data()[index] != '%')
            Terminal::put(format.data()[index]);
        else
        {
            switch (format.data()[index += 1])
            {
            case 'd': {
                auto number = reverse_number(*reinterpret_cast<int*>(variadic));

                do
                {
                    Terminal::put(char('0' + number % 10));
                }
                while (number /= 10);

                variadic += sizeof(int);
                break;
            }
            case 'v': {
                Terminal::put(*reinterpret_cast<StringView*>(variadic));
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
