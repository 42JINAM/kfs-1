#ifndef PIC_H
# define PIC_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

void	outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void	PIC_sendEOI(uint8_t irq);
#endif // !PIC_H
