extern syscall_handler

global syscall_common_stub
syscall_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov eax, ds
    push eax
    mov ax, 0x01
    mov ds, ax
    mov es, ax
    call syscall_handler
    pop eax
    mov ds, eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    iret
