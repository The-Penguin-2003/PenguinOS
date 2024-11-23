.PHONY: all install run clean

all: install run

install: kernel
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/kernel.bin
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o PenguinOS.iso iso

kernel: boot/bootstrap.o boot/gdt.o link.ld kernel/kernel.o kernel/io.o kernel/mem.o kernel/str.o drivers/vga.o kernel/kprintf.o drivers/serial.o kernel/gdt.o
	i686-elf-ld -m elf_i386 -T link.ld -o kernel.bin boot/bootstrap.o boot/gdt.o kernel/kernel.o kernel/io.o kernel/mem.o kernel/str.o drivers/vga.o kernel/kprintf.o drivers/serial.o kernel/gdt.o

kernel/%.o: kernel/%.c
	i686-elf-gcc -Wall -m32 -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -Wno-incompatible-pointer-types -Wno-discarded-qualifiers -c -o $@ $<

boot/%.o: boot/%.asm
	nasm -f elf -o $@ $<

kernel/%.o: kernel/%.asm
	nasm -f elf -o $@ $<

drivers/%.o: drivers/%.c
	i686-elf-gcc -Wall -m32 -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -Wno-incompatible-pointer-types -Wno-discarded-qualifiers -c -o $@ $<

run: PenguinOS.iso
	qemu-img create -f qcow2 PenguinOS.hdd 2G
	qemu-system-x86_64 -machine pc -cpu core2duo -m 512M -hda PenguinOS.hdd -cdrom PenguinOS.iso -vga std -display sdl -monitor stdio -rtc base=localtime -net none -boot order=d

clean:
	rm -rf iso *.iso *.bin boot/*.o kernel/*.o *.hdd drivers/*.o
