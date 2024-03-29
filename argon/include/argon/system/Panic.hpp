#pragma once

#include <libc/random.hpp>
#include <libcpp/Array.hpp>
#include <libcpp/StringView.hpp>

#include "Terminal.hpp"
#include "hardware/IO.hpp"
#include "hardware/VGA.hpp"
#include "system/descriptor/IDT.hpp"

void panic(StringView const message, auto&&... args)
{
    asm ("cli");

    Array static constexpr messages
    {
        "I did that?"_sv,
        "Note to self: Never touch the red button again."_sv,
        "Did I just press the self-destruct button?"_sv,
        "Would you look at that! I crashed!"_sv,
        "Well, that escalated quickly! I think I broke something."_sv,
        "No cookies for me :^("_sv,
        "Spicy!"_sv,
        "Just added extra spice to the code. Hope you like it."_sv,
        "Aliens must have hacked my computer... It's the only explanation."_sv,
        "My bad, wrong button."_sv,
        "Cookies mysteriously disappeared while I was away. Definitely not me."_sv,
        "Oops, my bad! I promise, I'm not usually this clumsy."_sv,
        "I may have accidentally created a black hole. Oops!"_sv,
        "Sorry... I'll do better next time!"_sv,
        "This is terrible! It must have been the aliens!"_sv,
        "My code works perfectly... in a parallel universe."_sv,
        "This error message is so cryptic, even the NSA can't decrypt it."_sv,
        "I added a 'fun' feature. Now the program randomly tells jokes."_sv,
    };

    port::outb(port::CMOS_COMMAND, port::cmos::SECONDS);
    libc::srand(port::inb(port::CMOS_DATA));

    VGA::clear_buffer();
    Terminal::putf("{}\n\n", messages[static_cast<uint32_t>(libc::rand()) % messages.size()]);

    Terminal::put("panic: ");

    Terminal::set_cursor_color({ VGAColor::LIGHT_RED, VGAColor::BLACK });

    if constexpr (sizeof...(args))
        Terminal::putf(message, args...);
    else
        Terminal::putln(message);

    asm ("hlt");
}

void panic(InterruptStack const* interruptStack, StringView const message);

