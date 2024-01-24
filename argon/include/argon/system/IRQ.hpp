#pragma once

#include "descriptor/IDT.hpp"

namespace irq {

void install(IDT& idt) noexcept;

}
