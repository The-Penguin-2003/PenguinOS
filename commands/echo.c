#include <commands.h>
#include <vga.h>

void echo_cmd(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        puts((uint8_t*)argv[i]);

        if (i < argc - 1)
            putc((uint8_t)' ');
    }

    puts((uint8_t*)"\n");
}
