#include <commands.h>
#include <vga.h>

void help_cmd(int argc, char* argv[]) {
    puts((unsigned char*)"Command List\r\n");
    puts((unsigned char*)"------------\r\n");
    puts((unsigned char*)"help - Displays this list\r\n");
    puts((unsigned char*)"echo - Echos a string to the console\r\n");
    puts((unsigned char*)"clear - Clears the screen\r\n");
    puts((unsigned char*)"reboot - Reboots the system\r\n");
}
