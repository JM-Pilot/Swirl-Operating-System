// MIT LICENSE 2025 JM-Pilot
// Warning code may break due to reasons
#include <limine.h>
#include <stdint.h>
#include <stddef.h>
#include <framebuffer.h>

// Enter a halt loop forever
void stop_sys(){
	for (;;){
		asm volatile ("hlt");
	}
}

void kernel_main(){
	init_framebuffer();
	for (int i = 0; i < 256; i++){
		plot_pixel(5, i, 0xFFFFFF);
	}
	stop_sys();
}