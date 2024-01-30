#include "hardware/hid/KeyBoard.hpp"

#include <libcpp/Array.hpp>
#include <libcpp/Pair.hpp>

#include "Assert.hpp"
#include "Terminal.hpp"
#include "hardware/IO.hpp"

enum class State
{
    PRESSED, RELEASED
};

static auto decode_normal_key(auto const scanCode)
{
    Array<Pair<uint32_t, char>, 66> static constexpr normalCodes
    {{
        { 0x02, '1' }, { 0x03, '2' }, { 0x04, '3' }, { 0x05, '4' }, { 0x06, '5' }, { 0x07, '6' }, { 0x08, '7' }, { 0x09, '8' }, { 0x0A, '9' }, { 0x0B, '0' }, { 0x0C, '-' }, { 0x0D, '=' }, { 0x0E, '\b' }, { 0x0F, '\t' },
        { 0x10, 'q' }, { 0x11, 'w' }, { 0x12, 'e' }, { 0x13, 'r' }, { 0x14, 't' }, { 0x15, 'y' }, { 0x16, 'u' }, { 0x17, 'i' }, { 0x18, 'o' }, { 0x19, 'p' }, { 0x1A, '[' }, { 0x1B, ']' }, { 0x1C, '\n' },
        { 0x1E, 'a' }, { 0x1F, 's' }, { 0x20, 'd' }, { 0x21, 'f' }, { 0x22, 'g' }, { 0x23, 'h' }, { 0x24, 'j' }, { 0x25, 'k' }, { 0x26, 'l' }, { 0x27, ';' }, { 0x28, '\'' }, { 0x29, '`' }, { 0x2B, '\\' },
        { 0x2C, 'z' }, { 0x2D, 'x' }, { 0x2E, 'c' }, { 0x2F, 'v' }, { 0x30, 'b' }, { 0x31, 'n' }, { 0x32, 'm' }, { 0x33, ',' }, { 0x34, '.' }, { 0x35, '/' }, { 0x37, '*' }, { 0x39, ' ' }, 
        { 0x47, '7' }, { 0x48, '8' }, { 0x49, '9' }, { 0x4A, '-' }, { 0x4B, '4' }, { 0x4C, '5' }, { 0x4D, '6' }, { 0x4E, '+' }, { 0x4F, '1' }, { 0x50, '2' }, { 0x51, '3' }, { 0x52, '0' }, { 0x53, '.' }, { 0x00, '\0' }
    }};

    for (auto code : normalCodes)
    {
        if (scanCode == code.first)
        // cppcheck-suppress useStlAlgorithm
        {
            return code.second;
        }
    }

    return '\0';
}

static auto decode_special_key(auto const scanCode)
{
    Array<Pair<uint32_t, char>, 60> static constexpr specialCodes =
    {{
        { 0x02, '!' }, { 0x03, '@' }, { 0x04, '#' }, { 0x05, '$' }, { 0x06, '%' }, { 0x07, '^' }, { 0x08, '&' }, { 0x09, '*' }, { 0x0A, '(' }, { 0x0B, ')' }, { 0x0C, '_' }, { 0x0D, '+' },
        { 0x10, 'Q' }, { 0x11, 'W' }, { 0x12, 'E' }, { 0x13, 'R' }, { 0x14, 'T' }, { 0x15, 'Y' }, { 0x16, 'U' }, { 0x17, 'I' }, { 0x18, 'O' }, { 0x19, 'P' }, { 0x1A, '{' }, { 0x1B, '}' },
        { 0x1E, 'A' }, { 0x1F, 'S' }, { 0x20, 'D' }, { 0x21, 'F' }, { 0x22, 'G' }, { 0x23, 'H' }, { 0x24, 'J' }, { 0x25, 'K' }, { 0x26, 'L' }, { 0x27, ':' }, { 0x29, '~' },
        { 0x2C, 'Z' }, { 0x2D, 'X' }, { 0x2E, 'C' }, { 0x2F, 'V' }, { 0x30, 'B' }, { 0x31, 'N' }, { 0x32, 'M' }, { 0x33, '<' }, { 0x34, '>' }, { 0x35, '?' }, { 0x37, '*' }, { 0x39, ' ' },
        { 0x47, '7' }, { 0x48, '8' }, { 0x49, '9' }, { 0x4A, '-' }, { 0x4B, '4' }, { 0x4C, '5' }, { 0x4D, '6' }, { 0x4E, '+' }, { 0x4F, '1' }, { 0x50, '2' }, { 0x51, '3' }, { 0x52, '0' }, { 0x53, '.' }
    }};

    for (auto code : specialCodes)
    {
        if (scanCode == code.first)
        // cppcheck-suppress useStlAlgorithm
        {
            return code.second;
        }
    }

    return '\0';
}

char keyboard_read_char(bool)
{
    kassert(false && "UNIMPLEMENTED");
    return 0;
}

void keyboard_driver(InterruptStack const*)
{
    auto const scanCode = inb(port::PS2_DATA);;

    auto static shiftState = State::RELEASED;

    if (!(scanCode & 0x80))
    {
        switch (scanCode)
        {
        case 0x2A: shiftState = State::PRESSED; return;
        }

        if (shiftState == State::RELEASED)
            Terminal::put(decode_normal_key(scanCode));
        else
            Terminal::put(decode_special_key(scanCode));
    }
    else switch (~(scanCode & 0x80) & scanCode)
    {
    case 0x2A: shiftState = State::RELEASED;
    }
}

