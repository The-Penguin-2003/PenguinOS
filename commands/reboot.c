#include <commands.h>
#include <io.h>

void reboot_cmd(int argc, char* argv[]) {
    while (inb(0x64) & 0x02);
    outb(0x64, 0xFE);

    while (1)
        asm volatile("hlt");
}
