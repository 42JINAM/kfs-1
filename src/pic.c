#include "pic.h"
#include "kernel.h"

// PIC ? 
// It's a chip for serving all hardware interrupts to CPU
// If keyboard send PIC an interrupt, PIC put the number and send it to CPU.
//
// The command port and dataport
// Command(0x20, 0xA0) : CPU -> PIC (Command) / PIC -> CPU (status / interrupts number)
// DATA (0x21, 0xA1) : configuration data 
//
// master and slaves 
// CPU - master - slave
// master 0 to 7
// slave 8 to 15
//

void outb(uint16_t port, uint8_t val)
{
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
    /* There's an outb %al, $imm8 encoding, for compile-time constant port numbers that fit in 8b. (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

void	PIC_sendEOI(uint8_t irq)
{
	if (irq >= 8)
		outb(PIC2_COMMAND, PIC_EOI);
	outb(PIC1_COMMAND, PIC_EOI);
}

// default configuration after booting :
// master 0 to 7 -> INT 0x08 - 0x0F
// slave 8 to 15 -> INT 0x70 - 0x77
// But INT 0x00 - 0x1F (0 ~ 31) are reserved for cpu exception
// so we have to move IRQ 0 - 15 to INT 0x20 - 0x2F 
//
void	io_wait()
{
	outb(0x80, 0);
}

void    PIC_remap(int offset1, int offset2)
{
	uint8_t	master = inb(PIC1_DATA);
	uint8_t	slave = inb(PIC2_DATA);
	
	//ICW1 : initiation + using ICW4 
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();

	outb(PIC1_DATA, offset1);
	io_wait();
	outb(PIC2_DATA, offset2);
	io_wait();

	outb(PIC1_DATA, 1 << CASCADE_IRQ);
	io_wait();
	outb(PIC2_DATA, CASCADE_IRQ);
	io_wait();

	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	outb(PIC1_DATA, master);
	outb(PIC2_DATA, slave);

}

// void	__attribute__((noinline)) IRQ_clear_mask(uint8_t IRQline)
// {
// 	uint16_t	port;
// 	uint8_t		value;
//
// 	printk("PIC1_DATA = 0x%x\n", PIC1_DATA);
//
// 	if(IRQline < 8)
// 	{
// 		port = PIC1_DATA;
// 	}
// 	else
// 	{
// 		port = PIC2_DATA;
// 		IRQline -= 8;
// 	}
// 	value = inb(port);
// 	value &= ~(1 << IRQline);
// 	outb(port, value);
// }

void IRQ_clear_mask(uint8_t IRQline)
{
	printk("IRQ_clear_mask(%d) called\n", IRQline);

	uint16_t	port;
	uint8_t		value;

	if (IRQline < 8) {
		port = PIC1_DATA;
	} else {
		port = PIC2_DATA;
		IRQline -= 8;
	}
	value = inb(port);
	value &= ~(1 << IRQline);
	outb(port, value);
}

void	IRQ_set_mask(uint8_t IRQline)
{
	uint16_t	port;
	uint8_t		value;

	if(IRQline < 8)
	{
		port = PIC1_DATA;
	}
	else
	{
		port = PIC2_DATA;
		IRQline -= 8;
	}
	value = inb(port);
	value |= (1 << IRQline);
	outb(port, value);
}
