#pragma once

#include <system/Panic.hpp>

#define kassert(condition) (condition) ? void() : (void)panic(__FILE_NAME__": {} @ {}: Assertion `" #condition "` failed.\n", __PRETTY_FUNCTION__, __LINE__)

