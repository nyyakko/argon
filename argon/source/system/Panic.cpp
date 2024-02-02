#include "system/Panic.hpp"

void panic(InterruptStack const* interruptStack, StringView const message)
{
    Terminal::putf("GS: {}\nFS: {}\nES: {}\nDS: {}\n", interruptStack->GS, interruptStack->FS, interruptStack->ES, interruptStack->DS);
    Terminal::putf("EDI: {}\nESI: {}\nEBP: {}\nESP: {}\nEDX: {}\nEDX: {}\nECX: {}\nEAX: {}\n", interruptStack->EDI, interruptStack->ESI, interruptStack->EBP, interruptStack->ESP, interruptStack->ESP, interruptStack->EDX, interruptStack->ECX, interruptStack->EAX);
    Terminal::putf("EIP: {}\nCS: {}\neflags: {}\nuserESP: {}\nSS: {}\n\n", interruptStack->EIP, interruptStack->CS, interruptStack->eflags, interruptStack->userESP, interruptStack->SS);

    panic(message);
}

