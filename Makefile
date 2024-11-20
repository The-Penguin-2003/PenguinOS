.PHONY: all install run clean

all: install run

install: kernel
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/kernel.bin
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o PenguinOS.iso iso

kernel: boot/bootstrap.o link.ld kernel/kernel.o
	i686-elf-ld -m elf_i386 -T link.ld -o kernel.bin boot/bootstrap.o kernel/kernel.o

kernel/%.o: kernel/%.c
	i686-elf-gcc -Wall -m32 -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o $@ $<

boot/%.o: boot/%.asm
	nasm -f elf -o $@ $<

run: PenguinOS.iso
	qemu-img create -f qcow2 PenguinOS.hdd 2G
	qemu-system-x86_64 -machine pc -cpu core2duo -m 512M -hda PenguinOS.hdd -cdrom PenguinOS.iso -rtc base=localtime -net none -boot order=d

clean:
	rm -rf iso *.iso *.bin boot/*.o kernel/*.o *.hdd
