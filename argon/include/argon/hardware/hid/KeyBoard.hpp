#pragma once

#include "system/descriptor/IDT.hpp"

char keyboard_read_char(bool fromIRQ = false);
void keyboard_driver(InterruptStack const*);

