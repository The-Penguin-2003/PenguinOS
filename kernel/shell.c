/* PenguinOS Shell */
#include <str.h>
#include <vga.h>
#include <kprintf.h>
#include <keyboard.h>
#include <shell.h>
#include <commands.h>

typedef void (*cmd_func_t)(int argc, char* argv[]);

typedef struct {
    const uint8_t* cmd_name;
    cmd_func_t cmd_function;
} cmd_t;

cmd_t commands[MAX_COMMANDS];
int32_t cmd_count = 0;

void register_cmd(const uint8_t* name, cmd_func_t function) {
    if (cmd_count < MAX_COMMANDS) {
        commands[cmd_count].cmd_name = name;
        commands[cmd_count].cmd_function = function;
        cmd_count++;
    }
}

cmd_func_t find_cmd(const uint8_t* name) {
    for (int32_t i = 0; i < cmd_count; i++) {
        if (strcmp(name, commands[i].cmd_name) == 0)
            return commands[i].cmd_function;
    }

    return 0;
}

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
    register_cmd((uint8_t*)"echo", echo_cmd);
    register_cmd((uint8_t*)"clear", clear_cmd);
    register_cmd((uint8_t*)"reboot", reboot_cmd);
    register_cmd((uint8_t*)"help", help_cmd);

    for (;;) {
        uint8_t input_buffer[BUFFER_SIZE];
        uint8_t* argv[MAX_ARGS];

        puts((uint8_t*)"> ");

        get_input(input_buffer, BUFFER_SIZE);
        puts((uint8_t*)"\n");

        int32_t argc = parse_input(input_buffer, argv, MAX_ARGS);

        if (argc == 0)
            continue;

        cmd_func_t cmd = find_cmd(argv[0]);
        if (cmd)
            cmd(argc, argv);
        else
            kprintf((uint8_t*)"Unknown Command: %s\r\n", argv[0]);
    }
}
