#include <commands.h>
#include <kprintf.h>

const int32_t OS_MAJOR_VERSION = 0;
const int32_t OS_MINOR_VERSION = 0;

void osver_cmd(int argc, char* argv[]) {
    kprintf((uint8_t*)"PenguinOS v%d.%d\r\n", OS_MAJOR_VERSION, OS_MINOR_VERSION);
}
