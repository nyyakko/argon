#include "system/Panic.hpp"

void panic(InterruptStack const* interruptStack, StringView const message)
{
    Terminal::putf("GS: %d\nFS: %d\nES: %d\nDS: %d\n", interruptStack->GS, interruptStack->FS, interruptStack->ES, interruptStack->DS);
    Terminal::putf("EDI: %d\nESI: %d\nEBP: %d\nESP: %d\nEDX: %d\nEDX: %d\nECX: %d\nEAX: %d\n", interruptStack->EDI, interruptStack->ESI, interruptStack->EBP, interruptStack->ESP, interruptStack->ESP, interruptStack->EDX, interruptStack->ECX, interruptStack->EAX);
    Terminal::putf("EIP: %d\nCS: %d\neflags: %d\nuserESP: %d\nSS: %d\n\n", interruptStack->EIP, interruptStack->CS, interruptStack->eflags, interruptStack->userESP, interruptStack->SS);

    panic(message);
}

