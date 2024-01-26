#include "Terminal.hpp"

void Terminal::put(char data, VGAColor const foreground, VGAColor const background)
{
    VGA::put_entry_at(VGAEntry(data, foreground, background));
}

void Terminal::put(StringView const data, VGAColor const foreground, VGAColor const background)
{
    for (auto index = 0lu; index < data.size(); index++)
    {
        put(data.data()[index], foreground, background);
    }
}

void Terminal::putln(StringView const data, VGAColor const foreground, VGAColor const background)
{
    put(data, foreground, background);
    put("\n"_sv, foreground, background);
}
