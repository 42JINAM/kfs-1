#include "ascii.h"
#include "../kernel.h"

static void	busy_wait(unsigned int count)
{
	volatile unsigned int	delay;

	delay = 0;
	while (delay < count)
		delay++;
}

void	print_ascii(void)
{
	const t_ascii_func	draw[25] = {\
		ascii_1, ascii_2, ascii_3, ascii_4, ascii_5, ascii_6, ascii_7, \
		ascii_8, ascii_9, ascii_10, ascii_11, ascii_12, ascii_13, ascii_14, \
		ascii_15, ascii_16, ascii_17, ascii_18, ascii_19, ascii_20, ascii_21, \
		ascii_22, ascii_23, ascii_24, ascii_25
	};
	int					i;

	init_terminal(&g_vga.t1, vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));
	flush_terminal(&g_vga.t1);
	i = 0;
	while (i < 25)
	{
		init_terminal(&g_vga.t1, vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));
		draw[i]();
		busy_wait(10000000);
		i++;
	}
}