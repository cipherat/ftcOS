BINPATH		= ${HOME}/opt/cross/bin

bootloader 	= boot.s
bootloader_out	= boot.o
ASM		= ${BINPATH}/i686-elf-as
ASMFLAGS	= 
ASMOUT		= -o ${bootloader_out}

kernel		= kernel.c
kernel_out	= kernel.o
CC		= ${BINPATH}/i686-elf-gcc
CCFLAGS		= -c ${kernel} -std=gnu99 -ffreestanding -O2 -Wall -Wextra
CCOUT		= -o ${kernel_out}

linker		= linker.ld
os_out		= ftcos.bin
LD		= ${BINPATH}/i686-elf-ld
LDFLAGS		= -T ${linker} -o {os_out} -ffreestanding -O2 -nostdlib ${bootloader_out} ${kernel_out} -lgcc

build:
	${ASM} ${bootloader} ${ASMFLAGS} ${ASMOUT}
	${CC} ${CCFLAGS} ${CCOUT}
	${CC} ${LDFLAGS}

boot:
	qemu-system-i386 -cdrom ftcos.iso
