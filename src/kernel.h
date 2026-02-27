#ifndef KERNEL_H
# define KERNEL_H 

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include "string.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
# if defined(__linux__)
	#error "You are not using a cross-compiler, you will most certainly run into trouble"
# endif

/* This tutorial will only work for the 32-bit ix86 targets. */
# if !defined(__i386__)
	#error "This tutorial needs to be compiled with a ix86-elf compiler"
# endif

/* Hardware text mode color constants. */
enum e_vga_color
{
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

/* 함수 선언 */
void	terminal_initialize(void);
void	terminal_setcolor(uint8_t color);
void	terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void	terminal_putchar(char c);
void	terminal_write(const char *data, size_t size);
void	terminal_writestring(const char *data);
void	kernel_main(void);

#endif /* KERNEL_H */
