#include "kernel.h"


void print_esp(uint32_t * addr)
{
	printf("test\n");
	printf("esp: %p %x\n", addr, *addr);
}

void	kernel_main(uint32_t *addr)
{
	g_vga.vga_buffer = (uint16_t *)VGA_MEMORY;

	// print_ascii();
	terminal_initialize();
	terminal_write_line("hello 42 world!\n");
	printf("eenough is enough : %p %x\n", addr, *addr);
	gdt_init();
	check_gdt_value();
	idt_initialize();
	check_idt_value();
  	uint32_t* my_esp;
	asm volatile("mov %%esp, %0" :"=r" (my_esp));
	print_esp(my_esp);

	keyboard_handler();
	}
