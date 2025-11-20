OUTPUT_FORMAT(elf64-x86-64)
ENTRY(kernel_main)
SECTIONS
{
	. = 0xFFFFFFFF80000000;
	.text (READONLY) : ALIGN(4)
	{
		*(.text)
	}

	.data (READONLY) : ALIGN(4)
	{
		*(.data)
	}

	.rodata (READONLY) : ALIGN(4)
	{
		*(.rodata)
	}

	.bss (READONLY) : ALIGN(4)
	{
		*(COMMON)
		*(.bss)
	}
}