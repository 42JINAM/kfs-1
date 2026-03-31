#include "interupt.h"
#include "utils/utils.h"
#include <stdint.h>
extern void *interupt_table[];

idt_entry*	idtr = (idt_entry*)IDT_ADDR;

void	general_handler(uint8_t vector)
{

	uint8_t	irq = vector - 32;
	printk("got ya IRQ %u\n", irq);
	if (irq == 9 - 32)
	{
		printk(">> %u\n", vector);
		keyboard_handler();
	}
	PIC_sendEOI(irq);
	// asm volatile("cli; hlt");
}

static void	create_descriptor(void *idt, uint8_t flags, uint8_t vector)
{
	idt_entry* temp = &idtr[vector];

	temp->flags = flags;
	temp->low_offset = (uint32_t)idt & 0xFFFF;
	temp->high_offset = (uint32_t)idt >> 16;
	temp->reserved = 0;
	temp->segment_offset = CS;
}

void check_idt_value() {
	for (int i = 0; i < 5; i++)
	{
		idt_entry* temp = (idt_entry*)IDT_ADDR + i;
		printf("index : %x %x %x %x %x\n", temp->low_offset, temp->segment_offset, temp->reserved, temp->flags, temp->high_offset);
	}
}


void	idt_initialize()
{
	idt_ptr	ptr;

	ptr.size = (uint16_t)(sizeof(idt_entry) * MAX_SIZE - 1);
	ptr.addr = (uint32_t)IDT_ADDR;

	for (uint8_t i = 0; i < 33; i++)
		create_descriptor(interupt_table[i], INTERUPT_GATE, i);

	asm volatile("lidt %0": :"m"(ptr));
	asm volatile("sti");
}
