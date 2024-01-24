#include "Panic.hpp"

#include "libc/random.hpp"

#include "hardware/VGA.hpp"
#include "hardware/io/IO.hpp"
#include "Terminal.hpp"

void panic(StringView const message)
{
    asm ("cli");

    static constexpr StringView messages[] =
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

    auto constexpr messagesCount = sizeof(messages) / sizeof(StringView);

    outb(port::CMOS_COMMAND, port::cmos::SECONDS);
    libc::srand(inb(port::CMOS_DATA));

    VGA::clear_buffer();
    Terminal::putln(messages[static_cast<uint32_t>(libc::rand()) % messagesCount]);
    Terminal::put("\n");

    Terminal::put("panic: ");
    Terminal::putln(message, VGAColor::LIGHT_RED);

    asm ("hlt");
}

