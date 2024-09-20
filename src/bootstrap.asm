;;; PenguinOS GRUB Bootstrap ;;;

[BITS 32]	; Using 32-bit code

;; Starting Point
global _start
_start:
	mov esp, _system_stack
	jmp _entry_stub

;; Multiboot Header
align 4
mb_header:
	MB_PAGE_ALIGN 	equ 1<<0
	MB_MEM_INFO 	equ 1<<1
	MB_AOUT_KLUDGE 	equ 1<<16
	MB_MAGIC_NUMBER equ 0x1BADB002
	MB_FLAGS 	equ MB_PAGE_ALIGN | MB_MEM_INFO | MB_AOUT_KLUDGE
	MB_CHECKSUM 	equ -(MB_MAGIC_NUMBER + MB_FLAGS)

	extern code, bss, end

	dd MB_MAGIC_NUMBER
	dd MB_FLAGS
	dd MB_CHECKSUM

	dd mb_header
	dd code
	dd bss
	dd end
	dd _start

;; Kernel Entry Point
_entry_stub:
	extern kernel_main
	call kernel_main
	jmp $

section .bss
	resb 8192
_system_stack:
;; THIS LINE INTENTIONALLY LEFT BLANK

