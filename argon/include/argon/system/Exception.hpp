#pragma once

#include "Terminal.hpp"

inline void interrupt_generic()
{
    Terminal::putln("unknown interrupt");
}

void interrupt_0();
void interrupt_1();
void interrupt_2();
void interrupt_3();
void interrupt_4();
void interrupt_5();
void interrupt_6();
void interrupt_7();
void interrupt_8();
void interrupt_9();
void interrupt_10();
void interrupt_11();
void interrupt_12();
void interrupt_13();
void interrupt_14();
void interrupt_16();
void interrupt_17();
void interrupt_18();
void interrupt_19();
void interrupt_20();
void interrupt_21();

