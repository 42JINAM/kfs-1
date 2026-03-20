#include "kernel.h"

#define GET_ESP(x) asm volatile("mov %%esp, %0" : "=r"(x) ::)
#define GET_EBP(x) asm volatile("mov %%ebp, %0" : "=r"(x) ::)

void	kernel_main(void)
{
	gdt_init();
	g_vga.vga_buffer = (uint16_t *)VGA_MEMORY;

	// print_ascii();
	terminal_initialize();
	terminal_write_line("hello 42 world!\n");

  	check_gdt_value();
  
	keyboard_handler();
}
