#include "interupt.h"
#include "utils/utils.h"
extern void *interupt_table[];

idt_entry*	idtr = (idt_entry*)IDT_ADDR;

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
	while (number > 0)
	{
		buff[i++] = digits[number % 10];
		number /= 10;
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
		*str++;
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

void	general_handler(uint8_t vector)
{
	printk("got ya %u\n", vector);
	asm volatile("cli; hlt");
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

	for (uint8_t i = 0; i < 32; i++)
		create_descriptor(interupt_table[i], INTERUPT_GATE, i);

	asm volatile("lidt %0": :"m"(ptr));
	asm volatile("sti");
}
