#include "printk.h"
static void	print_number(int number)
{
	char			digits[] = "0123456789";
	char			buff[32] ;
	int				i = 0;
	unsigned int	u;

	if (number == 0)
		terminal_write_char('0');
	if (number < 0)
	{
		terminal_write_char('-');
		u = (unsigned int)-number;
	}
	else
		u = (unsigned int)number;
	while (u > 0)
	{
		buff[i++] = digits[u % 10];
		u /= 10;
	}

	while (i--)
		terminal_write_char(buff[i]);
}

static void	print_uint(uint32_t number, int base)
{
	char			digits[] = "0123456789ABCDEF";
	char			buff[32] ;
	int				i = 0;

	if (number == 0)
		terminal_write_char('0');
	while (number > 0)
	{
		buff[i++] = digits[number % base];
		number /= base;
	}
	while (i--)
		terminal_write_char(buff[i]);
}

void printk(char *str, ...)
{
	va_list	args;
	va_start(args, str);

	//duxcs%
	while (*str)
	{
		if (*str != '%')
		{
			terminal_write_char(*str++);
			continue ;
		}
		str++;
		switch(*str)
		{
			case 'd':
				print_number(va_arg(args, int));
				break;
			case 'u':
				print_uint((uint32_t)va_arg(args, unsigned int), 10);
				break;
			case 'x':
				print_uint((uint32_t)va_arg(args, unsigned int), 16);
				break;
			case 'p':
				print_uint(va_arg(args, uint32_t), 16);
				break;
			case 'c':
				terminal_write_char((char)va_arg(args, int));
				break;
			case 's':
				terminal_write_line(va_arg(args, char *));
				break;
			case '%':
				terminal_write_char('%');
				break;
			default:
				terminal_write_char('%');
				terminal_write_char(*str);
				break;
		}
		str++;
	}
	va_end(args);
}
