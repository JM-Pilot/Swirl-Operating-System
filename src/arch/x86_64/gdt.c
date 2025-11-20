#include <arch/x86_64/gdt.h>
#include <stdint.h>
#include <kernel.h>
// Target = GDT_Table
// Source = GDT Segment
void encode_GDT(uint8_t *target, struct GDT source){
	if (source.limit > 0xFFFFF){
		stop_sys();		// Replace this later if fonts have appear
	}
	// Encode Limit
	target[0] = source.limit & 0xFF;
	target[1] = (source.limit >> 8) & 0xFF;
	target[6] = (source.limit >> 16) & 0xFF;
	
	// Encode Base
	target[2] = source.base & 0xFF;
	target[3] = (source.base >> 8) & 0xFF;
	target[4] = (source.base >> 16) & 0xFF;
	target[7] = (source.base >> 24) & 0xFF;

	// Encode Access Byte
	target[5] = source.access_byte;
   	// Encode Flags
    	target[6] |= (source.flags & 0xFF) << 4;
}