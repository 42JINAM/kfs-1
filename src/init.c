#include "kernel.h" 

void	set_background(uint16_t* buffer, uint16_t entry) {
	int idx;

	for (int y = 0; y < VGA_HEIGHT; y++) {
		for (int x = 0; x < VGA_WIDTH; x++) {
			idx = y * VGA_WIDTH + x;
			buffer[idx] = entry;
		}
	}
}

void	set_terminal(t_terminal *t, uint16_t color)
{
	t->col = 0;
	t->row = 0;
	t->color = color;
	set_background(t->buffer, vga_entry(' ', color));
}

void	terminal_initialize(void)
{
	set_terminal(&g_vga.t1, vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
	set_terminal(&g_vga.t2, vga_entry_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_RED));
	flush_terminal(&g_vga.t1);
	g_vga.t1_switch = true;
}
