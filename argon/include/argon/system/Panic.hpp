#pragma once

#include <libcpp/StringView.hpp>

#include "system/descriptor/IDT.hpp"

void panic(InterruptStack const* interruptStack, StringView const message);

