#include "gdt.h"

struct gdt_entry gdt[7];
struct gdt_ptr gp;

extern void gdt_flush(uint32_t);

void gdt_set_gate(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt[index].base_low = base & 0xFFFF;           // 2 bytes
    gdt[index].base_middle = (base >> 16) & 0xFF;  // 1 bytes
    gdt[index].base_high = (base >> 24) & 0xFF;    // 1 bytes

    gdt[index].limit_low = limit & 0xFFFF;         // 2 bytes
    gdt[index].granularity = (limit >> 16) & 0x0F; // 0.5 bytes

    gdt[index].granularity |= gran & 0xF0;         // 0.5 bytes
    gdt[index].access = access;                    // 1 bytes
}

void gdt_init()
{
    // Set the size of the GDT (total bytes - 1), the base address of the GDT
    gp.limit = (sizeof(struct gdt_entry) * 7) - 1;
    gp.base = (uint32_t)&gdt;

    gdt_set_gate(0, 0, 0, 0, 0);                 // null

   //            i  b  limit       access gran       
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);  // kernel code
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);  // kernel data
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0x92, 0xCF);  // kernel stack

    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xFA, 0xCF);  // user code
    gdt_set_gate(5, 0, 0xFFFFFFFF, 0xF2, 0xCF);  // user data
    gdt_set_gate(6, 0, 0xFFFFFFFF, 0xF2, 0xCF);  // user stack

    // Load the new GDT into the CPU
    gdt_flush((uint32_t)&gp);
}