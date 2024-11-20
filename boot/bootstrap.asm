;;; PenguinOS GRUB Bootstrap ;;;

[BITS 32]   ; Using 32-bit code

;; Starting Point
global _start
_start:
    mov esp, _system_stack
    jmp entry_stub

;; Multiboot Header
align 4
mboot:
    MBOOT_PAGE_ALIGN equ 1<<0
    MBOOT_MEM_INFO equ 1<<1
    MBOOT_MAGIC equ 0x1BADB002
    MBOOT_FLAGS equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
    MBOOT_CHECKSUM equ -(MBOOT_MAGIC + MBOOT_FLAGS)

    extern code, bss, end

    dd MBOOT_MAGIC
    dd MBOOT_FLAGS
    dd MBOOT_CHECKSUM

    dd mboot
    dd code
    dd bss
    dd end
    dd _start

;; Kernel Entry Point
entry_stub:
    extern kernel_main
    call kernel_main
    jmp $

;; BSS Stuff
section .bss
    resb 8192   ; Reserve 8KB of memory
_system_stack:
;; THIS LINE INTENTIONALLY LEFT BLANK
