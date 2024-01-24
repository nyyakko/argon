#include "Terminal.hpp"

void Terminal::put(StringView const data, VGAColor const foreground, VGAColor const background)
{
    for (auto index = 0zu; index < data.size(); index++)
    {
        VGA::put_entry_at(VGAEntry(data.data()[index], foreground, background));
    }
}

void Terminal::putln(StringView const data, VGAColor const foreground, VGAColor const background)
{
    put(data, foreground, background);
    put("\n"_sv, foreground, background);
}
