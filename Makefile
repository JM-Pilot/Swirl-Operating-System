CC = x86_64-elf-gcc
NASM = nasm -f elf64
BIN = bin
SRC = src
C_FLG = -ffreestanding -O2 -mcmodel=kernel -nostdlib
L_FLG = -nostdlib
I_FLG = -Iinc
ISO_DIR = boot
IMG_NAME = SwirlOS

clean:
	rm -rf ${BIN}/*
	rm boot/bin/kernel.bin
compile:
	rm -rf ${BIN}
	mkdir ${BIN}
	${CC} -c ${I_FLG} ${SRC}/kernel.c -o ${BIN}/kernel.o ${C_FLG}

	${CC} -c ${I_FLG} ${SRC}/drivers/framebuffer.c -o ${BIN}/framebuffer.o ${C_FLG}
	${CC} -c ${I_FLG} ${SRC}/arch/x86_64/gdt.c -o ${BIN}/gdt_c.o ${C_FLG}

	${NASM} -felf64 ${SRC}/arch/x86_64/gdt.s -o ${BIN}/gdt_s.o 

link: compile
	${CC} -T ${SRC}/linker.ld \
		${BIN}/kernel.o ${BIN}/framebuffer.o ${BIN}/gdt_c.o ${BIN}/gdt_s.o \
		-o ${BIN}/kernel.bin ${L_FLG}

iso: link 
	cp ${BIN}/kernel.bin ${ISO_DIR}/bin/kernel.bin

	xorriso -as mkisofs -R -r -J -b limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus \
		-apm-block-size 2048 --efi-boot limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		${ISO_DIR}/ -o ${BIN}/${IMG_NAME}.iso

run: iso
	qemu-system-x86_64 -cdrom ${BIN}/${IMG_NAME}.iso \
		-m 2048 -no-reboot -no-shutdown \
		-bios ${ISO_DIR}/EFI/OVMF.4m.fd \
		-serial stdio
run-w-rebuild:
	qemu-system-x86_64 -cdrom ${BIN}/${IMG_NAME}.iso \
		-m 2048 -no-reboot -no-shutdown \
		-bios ${ISO_DIR}/EFI/OVMF.4m.fd \
		-serial stdio