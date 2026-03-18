#include "gdt.h"

t_gdt_entry *gdt = (t_gdt_entry *)GDT_ADDRESS;
t_gdt_ptr   *gp = (t_gdt_ptr *)(GDT_ADDRESS + sizeof(t_gdt_entry) * 7);

extern void gdt_flush(uint32_t);

void create_descriptor(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
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
    gp->limit = (sizeof(t_gdt_entry) * 7) - 1;
    gp->base = (uint32_t)gdt;

    create_descriptor(0, 0, 0, 0, 0);                 // null

    //                i  b  limit      access gran       
    create_descriptor(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);  // kernel code
    create_descriptor(2, 0, 0xFFFFFFFF, 0x92, 0xCF);  // kernel data
    create_descriptor(3, 0, 0xFFFFFFFF, 0x92, 0xCF);  // kernel stack

    create_descriptor(4, 0, 0xFFFFFFFF, 0xFA, 0xCF);  // user code
    create_descriptor(5, 0, 0xFFFFFFFF, 0xF2, 0xCF);  // user data
    create_descriptor(6, 0, 0xFFFFFFFF, 0xF2, 0xCF);  // user stack

    // Load the new GDT into the CPU
    gdt_flush((uint32_t)gp);
}

void check_gdt_value() {
    printf("gdt: %p\n", (uint32_t)gdt);
    printf("gp: %p\n", (uint32_t)gp);
    printf("gp->base: %p\n", (uint32_t)gp->base);
    printf("gp->limit: %p\n", (uint32_t)gp->limit);
    hexdump((uint32_t)gdt, 128);
}