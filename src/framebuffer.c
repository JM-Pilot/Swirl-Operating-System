// MIT LICENSE 2025 JM-Pilot
// Warning code may break due to reasons
#include <framebuffer.h>
#include <stdint.h>
#include <stddef.h>
#include <kernel.h>
struct limine_framebuffer *framebuffer;

// Get UEFI GOP and Request a framebuffer from limine
__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
	.id = LIMINE_FRAMEBUFFER_REQUEST_ID,
	.revision = 0
};

// Very Important and if not called no output will be seen
void init_framebuffer(){
	if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1){
		stop_sys();
	}

	framebuffer = framebuffer_request.response->framebuffers[0];
}

void plot_pixel(int x, int y, uint32_t col){
	uint32_t rel_pos = x * framebuffer->width + y;
	uint32_t *framebuffer_ptr = framebuffer->address;
	framebuffer_ptr[rel_pos] = col;
}
