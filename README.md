# PenguinOS
The Penguin Operating System

# What is PenguinOS?
PenguinOS is an operating system I am creating just to give myself something to work on when I'm bored.

# Building PenguinOS
As of now, the only way to use PenguinOS is to build from source.

In order to build PenguinOS from source, you will need:
- [GCC Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler) <- Instructions for how to build a GCC cross-compiler provided here
- GNU Make
- grub-mkrescue
- nasm
- xorriso (for grub-mkrescue)
- qemu

Once you have obtained the above resources, clone the respository using either `git clone https://www.github.com/The-Penguin-2003/PenguinOS` or `gh repo clone The-Penguin-2003/PenguinOS`.
When the repository has been cloned, simply run `make` to build PenguinOS and `make run` to boot it in QEMU.
