#ifndef INTERUPT_H
#define INTERUPT_H
#include <stdint.h>
#define MAX_SIZE 255
#define IDT_ADDR 0xF00
#define CS 0x08
#define TASK_GATE 0x85
#define INTERUPT_GATE 0x8E
#define TRAP_GATE 0x8F

typedef struct {
	uint16_t	low_offset;
	uint16_t	segment_offset;
	uint8_t		reserved;
	uint8_t		flags;
	uint16_t	high_offset;
}	__attribute__((packed)) idt_entry;

typedef struct {
	uint16_t	size;
	uint32_t	addr;
}	__attribute__((packed)) idt_ptr;

void	idt_initialize();
void	general_handler(uint8_t vector);
void check_idt_value();

#endif
