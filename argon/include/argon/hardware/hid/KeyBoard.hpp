#pragma once

#include <libcpp/Array.hpp>
#include <libcpp/Pair.hpp>
#include <libcpp/Concepts.hpp>

#include "system/descriptor/IDT.hpp"

enum class State
{
    PRESSED, RELEASED
};

class KeyBoard
{
public:

    static KeyBoard& initialize()
    {
        KeyBoard static keyboard {};
        return keyboard;
    }

    static KeyBoard& the() { return KeyBoard::initialize(); }

    static void keyboard_driver(InterruptStack const*);
    static Pair<uint32_t, char> get_last_pressed_scancode();

    static void read(ArrayConcept auto& buffer)
    {
        auto index = 0zu;

        while (index != buffer.size())
        {
            auto const [_, key] = KeyBoard::get_last_pressed_scancode();

            if (key == '\n') break;
            else if (key == '\b' && index >= 1)
            {
                buffer[index - 1] = 0;
                index -= 1;
            }
            else
            {
                buffer[index % buffer.size()] = key;
                index += 1;
            }
        }
    }

private:
    State shift_m { State::RELEASED };
    Pair<uint32_t, char> lastPressedKey_m {};
};


