; Code made by OSDEV Wiki and Some from HorizonOS
BITS 64
default rel
SECTION .data
align 16
gdtr 	DW 0 ; For limit storage
     	DQ 0 ; For base storage

global setGDT
setGDT:
	lgdt [rel gdtr]
	ret

global reloadSegments
reloadSegments:
	push 0x08
	push rax
	mov rax, [rel .reloadCS]
	retf
.reloadCS:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret