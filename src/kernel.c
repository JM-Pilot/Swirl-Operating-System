// MIT LICENSE 2025 JM-Pilot
// Warning code may break due to reasons
#include <limine.h>
#include <stdint.h>
#include <stddef.h>
#include <drivers/framebuffer.h>
#include <arch/x86_64/gdt.h>
// Enter a halt loop forever
void stop_sys(){
	for (;;){
		asm volatile ("hlt");
	}
}

void kernel_main(){
	struct GDT Null_seg = {0,0,0,0};
	struct GDT Code_Seg;
	Code_Seg.base = 0x0;
	Code_Seg.limit = 0xFFFFF;
	Code_Seg.access_byte = 0x9A;
	Code_Seg.flags = 0xA;
	
	struct GDT Data_Seg;
	Data_Seg.base = 0x0;
	Data_Seg.limit = 0xFFFFF;
	Data_Seg.access_byte = 0x9C;
	Data_Seg.flags = 0xA;

	uint8_t GDT_Table[3 * 8];

	encode_GDT(&GDT_Table[0], Null_seg);
	encode_GDT(&GDT_Table[8], Code_Seg);
	encode_GDT(&GDT_Table[16], Data_Seg);

	struct GDTR gdtptr;
	gdtptr.size = sizeof(GDT_Table) - 1;
	gdtptr.offset = (uint64_t)&GDT_Table;

	setGDT(&gdtptr); 
	// For some reason this breaks everything if you uncomment
	//reloadSegments();

	init_framebuffer();
	for (int i = 0; i < 256; i++){
		plot_pixel(5, i, 0xFFFFFF);
	}
	stop_sys();
}