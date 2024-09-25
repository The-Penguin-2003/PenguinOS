.PHONY: all clean install run

all: kernel install

install: kernel
	mkdir -p iso/boot/grub
	cp kernel.elf iso/boot/kernel.elf
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o PenguinOS.iso iso

kernel: bootstrap.o link.ld kernel.o io.o string.o vga.o gdt.o kprintf.o idt.o isrs.o irq.o syscall.o
	i686-elf-ld -m elf_i386 -T link.ld -o kernel.elf bootstrap.o kernel.o io.o string.o vga.o gdt.o kprintf.o idt.o isrs.o irq.o syscall.o

%.o: src/%.c
	i686-elf-gcc -Wall -Wno-incompatible-pointer-types -Wno-pointer-sign -m32 -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o $@ $<

%.o: src/%.asm
	nasm -f elf -o $@ $<

run: PenguinOS.iso
	qemu-system-i386 -cdrom PenguinOS.iso

clean:
	rm -rf iso *.o kernel.elf *.iso
