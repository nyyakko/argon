#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <cpuid.h>

#include "VGA.hpp"
#include "ReadWriteBuffer.hpp"
#include "libcpp/Pair.hpp"

namespace kbdriver {

    namespace detail {

    struct ScanCode
    {
        uint8_t code;
        char byte;
    };

    auto scancode_to_ascii(auto const scanCode)
    {
        static constexpr ScanCode scanCodes[] =
        {
            { 0x02, '1' }, { 0x03, '2' }, { 0x04, '3' }, { 0x05, '4' }, { 0x06, '5' }, { 0x07, '6' }, { 0x08, '7' }, { 0x09, '8' }, { 0x0A, '9' }, { 0x0B, '0' }, { 0x0C, '-' }, { 0x0D, '=' }, { 0x0E, '\b' }, { 0x0F, '\t' },
            { 0x10, 'q' }, { 0x11, 'w' }, { 0x12, 'e' }, { 0x13, 'r' }, { 0x14, 't' }, { 0x15, 'y' }, { 0x16, 'u' }, { 0x17, 'i' }, { 0x18, 'o' }, { 0x19, 'p' }, { 0x1A, '[' }, { 0x1B, ']' }, { 0x1C, '\n' },
            { 0x1E, 'a' }, { 0x1F, 's' }, { 0x20, 'd' }, { 0x21, 'f' }, { 0x22, 'g' }, { 0x23, 'h' }, { 0x24, 'j' }, { 0x25, 'k' }, { 0x26, 'l' }, { 0x27, ';' }, { 0x28, '\'' }, { 0x29, '`' }, { 0x2B, '\\' },
            { 0x2C, 'z' }, { 0x2D, 'x' }, { 0x2E, 'c' }, { 0x2F, 'v' }, { 0x30, 'b' }, { 0x31, 'n' }, { 0x32, 'm' }, { 0x33, ',' }, { 0x34, '.' }, { 0x35, '/' }, { 0x37, '*' }, { 0x39, ' ' }, { 0x47, '7' },
            { 0x48, '8' }, { 0x49, '9' }, { 0x4A, '-' }, { 0x4B, '4' }, { 0x4C, '5' }, { 0x4D, '6' }, { 0x4E, '+' }, { 0x4F, '1' }, { 0x50, '2' }, { 0x51, '3' }, { 0x52, '0' }, { 0x53, '.' }, { 0x00, '\0' }
        };

        for (auto code : scanCodes)
        {
            if (scanCode == code.code)
            {
                return code.byte;
            }
        }

        return '\0';
    }

    }

void read_input(auto* destination, auto const destinationSize)
{
    auto pressed = false;
    auto index   = 0zu;

    while (index < destinationSize)
    {
        auto const scancode = io::inb(io::ports::BIOS_IO_PORT);

        if (!pressed && (scancode & 128) != 128)
        {
            if (scancode >= 0x00 && scancode <= 0x53)
            {
                auto const code = detail::scancode_to_ascii(scancode);

                VGA::put(code);

                if (code != '\0' && code != '\n')
                {
                    destination[index++] = code;
                }
                else if (code == '\n')
                {
                    break;
                }
            }

            pressed = true;
        }
        else if ((scancode & 128) == 128)
        {
            pressed = false;
        }
    }

    io::outb(io::ports::BIOS_IO_PORT, 0);
}

}

extern "C" void kmain(void)
{
    VGA::initialize();

    static constexpr Pair<StringView, void(*)(void)> commands[]
    {
        { "why"_sv, [] {
            VGA::putln("i mean, its fun? right?");
        }},
        { "who"_sv, [] {
            VGA::putln("the same random guy from before.");
        }},
        { "missile"_sv, [] {

            VGA::putln(R"(  /\  )");
            VGA::putln(R"( /  \ )");
            VGA::putln(R"( |  | )");
            VGA::putln(R"( |  | )");
            VGA::putln(R"(/ == \)");
            VGA::putln(R"(|/**\|)");

            VGA::put("\n");

            VGA::putln("The missile knows where it is at all times.");
            VGA::putln("It knows this because it knows where it isn't, ");
            VGA::putln("by subtracting where it is, from where it isn't, ");
            VGA::putln("or where it isn't, from where it is, whichever is greater, ");
            VGA::putln("it obtains a difference, or deviation.");
        }},
        { "say"_sv, [] {
            ReadWriteBuffer buffer {};
            VGA::putln("what should i say?");
            VGA::put(": ");
            kbdriver::read_input(buffer.data(), buffer.size());
            VGA::putln(buffer.data());
        }}
    };

    VGA::putln("Available commands: ", VGAColor::LIGHT_MAGENTA);
    for (auto command : commands)
    {
        VGA::putln(command.first);
    }

    VGA::put("\n");

    while (true)
    {
        ReadWriteBuffer buffer {};
        kbdriver::read_input(buffer.data(), buffer.size());

        for (auto command : commands)
        {
            if (command.first == buffer.data()) { command.second(); }
        }
    }
}

