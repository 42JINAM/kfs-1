#include "interupt.h"
#include "keyboard.h"
#include "pic.h"
#include "terminal.h"
#include "utils/utils.h"
#include <stdint.h>
extern void *interupt_table[];

idt_entry*	idtr = (idt_entry*)IDT_ADDR;

void	general_handler(uint8_t vector)
{
	// printk("general_handler called, vector = %u\n", vector);

	if (vector < 32)
	{
		printk("BUG: exception vector %d (not IRQ)\n", vector);
		// return ;
		asm volatile("cli; hlt");
	}
	uint8_t irq = vector - 32;
	if (irq == 1)
	{
		keyboard_handler();
	}
	if (irq < 16)
		PIC_sendEOI(irq);
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

	// 0 - 31
	for (uint8_t i = 0; i < 32; i++)
		create_descriptor(interupt_table[i], INTERUPT_GATE, i);

	//IRQ 0 - 15 (32 - 47)
	for (uint8_t irq = 0; irq < 16; irq++)
		create_descriptor(interupt_table[32 + irq], INTERUPT_GATE, 32 + irq);

	PIC_remap(0x20, 0x28);
	IRQ_set_mask(0);
	IRQ_clear_mask(1);
	asm volatile("lidt %0": :"m"(ptr));
	asm volatile("sti");
	terminal_write_line("sti called waiting interrupts...\n");
	// asm volatile("xorl %%eax, %%eax\n\t"
	// 		 "divl %%eax"             // 0으로 나누기 → 예외 0
	// 		 ::: "eax");
}
