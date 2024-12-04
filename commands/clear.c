#include <commands.h>
#include <vga.h>

void clear_cmd(int argc, char* argv[]) {
    for (int i = 0; i < 25; i++)
        puts((unsigned char*)"\r\n");
}
