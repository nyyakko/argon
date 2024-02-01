#pragma once

#include <libcpp/Array.hpp>
#include <libcpp/Pair.hpp>

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
        class KeyBoard static the {};
        return the;
    }

    static KeyBoard& the() { return KeyBoard::initialize(); }

    static void keyboard_driver(InterruptStack const*);
    static Pair<uint32_t, char> get_last_pressed_scancode();

private:
    [[maybe_unused]]State shift_m { State::RELEASED };
    Pair<uint32_t, char> lastPressedKey_m {};
};


