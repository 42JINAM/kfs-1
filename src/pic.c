#include "pic.h"

// PIC?
// The command port and dataport
// Command(0x20, 0xA0) : CPU -> PIC (Command) / PIC -> CPU (status / interrupts number)
// DATA (0x21, 0xA1) : configuration data 
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
		outb(PIC2_COMMAND, PIC1);
	outb(PIC1_COMMAND, PIC1);
}

void    PIC_remap(int offset1, int offset2)
{

}
