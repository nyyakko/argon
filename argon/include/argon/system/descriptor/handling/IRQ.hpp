#pragma once

#include "system/descriptor/IDT.hpp"

namespace irq {

void install(IDT& idt);

}
