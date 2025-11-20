// MIT LICENSE 2025 JM-Pilot
// Warning code may break due to reasons
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <limine.h>
#include <stdint.h>
extern struct limine_framebuffer *framebuffer;

void init_framebuffer();
void plot_pixel(int x, int y, uint32_t col);
#endif