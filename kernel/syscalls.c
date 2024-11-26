#include <kprintf.h>
#include <syscalls.h>

void handle_syscall(int32_t syscall_num) {
    switch (syscall_num) {
        case 1:
            kprintf((uint8_t*)"Syscall 1\r\n");
            break;
        default:
            kprintf((uint8_t*)"ERROR: Invalid Syscall Number -> %d\r\n", syscall_num);
            break;
    }
}

void syscall_handler() {
    int32_t syscall_num;
    void* arg;

    asm volatile("mov %%eax, %0" : "=r"(syscall_num));
    asm volatile("mov %%ebx, %0" : "=r"(arg));

    handle_syscall(syscall_num);
}
