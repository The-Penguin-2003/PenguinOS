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

;; GDT
global gdt_flush
extern gp

gdt_flush:
	lgdt [gp]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush2
flush2:
	ret

global idt_load
extern idtp

idt_load:
	lidt [idtp]
	ret

%macro ISR_NOERRCODE 1
	global isr%1
	isr%1:
		cli
		push byte 0
		push byte %1
		jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
	global isr%1
	isr%1:
		cli
		push byte %1
		jmp isr_common_stub
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

extern fault_handler

isr_common_stub:
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp
	push eax
	mov eax, fault_handler
	call eax
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret

%macro IRQ 2
	global irq%1
	irq%1:
		cli
		push byte 0
		push byte %2
		jmp irq_common_stub
%endmacro

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

extern irq_handler

irq_common_stub:
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp
	push eax
	mov eax, irq_handler
	call eax
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret

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

section .bss
	resb 8192
_system_stack:
;; THIS LINE INTENTIONALLY LEFT BLANK

