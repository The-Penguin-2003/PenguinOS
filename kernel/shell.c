/* PenguinOS Shell */
#include <str.h>
#include <vga.h>
#include <kprintf.h>
#include <keyboard.h>
#include <shell.h>

int32_t parse_input(uint8_t* input, uint8_t* argv[], int32_t max_args) {
    int32_t argc = 0;
    uint8_t* tok = strtok(input, (uint8_t*)" ");

    while (tok != NULL && argc < max_args - 1) {
        argv[argc++] = tok;
        tok = strtok(NULL, (uint8_t*)" ");
    }

    argv[argc] = NULL;
    return argc;
}

void init_shell() {
    for (;;) {
        uint8_t input_buffer[BUFFER_SIZE];
        uint8_t* argv[MAX_ARGS];

        puts((uint8_t*)"> ");

        get_input(input_buffer, BUFFER_SIZE);
        puts((uint8_t*)"\n");

        int32_t argc = parse_input(input_buffer, argv, MAX_ARGS);

        if (argc == 0)
            continue;

        kprintf((uint8_t*)"Unknown Command: %s\r\n", argv[0]);
    }
}
