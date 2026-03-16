#include "kernel.h"

void	kernel_main(void)
{
  gdt_init();
	g_vga.vga_buffer = (uint16_t *)VGA_MEMORY;

	// print_ascii();
	terminal_initialize();
	terminal_write_line("hello 42 world!\n");
	
	keyboard_handler();
}
