#ifndef GDT_H
#define GDT_H

#include <stdint.h>

struct GDTR {
	uint16_t size;
	uint64_t offset;
}__attribute__((packed));

struct GDT {
	uint8_t base;
	uint32_t limit;
	uint16_t access_byte;
	uint8_t flags;
}__attribute__((packed));

extern void setGDT(struct GDTR *gdtr);
extern void reloadSegments(void);

void encode_GDT(uint8_t *target, struct GDT source);

#endif