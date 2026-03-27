#include "gdt.h"

t_gdt_entry *gdt = (t_gdt_entry *)GDT_ADDRESS;
t_gdtr	    gdtr;

extern void gdt_flush(uint32_t);

void create_descriptor(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flag)
{
    gdt[index].base_low = base & 0xFFFF;           // 2 bytes
    gdt[index].base_middle = (base >> 16) & 0xFF;  // 1 bytes
    gdt[index].base_high = (base >> 24) & 0xFF;    // 1 bytes

    gdt[index].limit_low = limit & 0xFFFF;         // 2 bytes
    gdt[index].granularity = (limit >> 16) & 0x0F; // 0.5 bytes

    gdt[index].granularity |= flag & 0xF0;         // 0.5 bytes
    gdt[index].access = access;                    // 1 bytes
}

void gdt_init()
{
    // Set the size of the GDT (total bytes - 1), the base address of the GDT
    gdtr.limit = (sizeof(t_gdt_entry) * NUM_GDT_ENTRIES) - 1;
    gdtr.base = (uint32_t)gdt;

    create_descriptor(0, 0, 0, 0, 0); // null

    //                i  b  limit          access           flag
    create_descriptor(1, 0, GDT_LIMIT_4GB, GDT_CODE_KERNEL, GDT_FLAG_32BIT);  // kernel code
    create_descriptor(2, 0, GDT_LIMIT_4GB, GDT_DATA_KERNEL, GDT_FLAG_32BIT);  // kernel data
    create_descriptor(3, 0, GDT_LIMIT_4GB, GDT_STACK_KERNEL, GDT_FLAG_32BIT);  // kernel stack

    create_descriptor(4, 0, GDT_LIMIT_4GB, GDT_CODE_USER,   GDT_FLAG_32BIT);  // user code
    create_descriptor(5, 0, GDT_LIMIT_4GB, GDT_DATA_USER,   GDT_FLAG_32BIT);  // user data
    create_descriptor(6, 0, GDT_LIMIT_4GB, GDT_STACK_USER,   GDT_FLAG_32BIT);  // user stack
    
    printf("gdt[2] access: %p\n", gdt[2].access);

    // Load the new GDT into the CPU
    gdt_flush((uint32_t)&gdtr);
}

void check_gdt_value() {
    printf("gdt: %p\n", (uint32_t)gdt);
    printf("gdtr: %p\n", &gdtr);
    printf("gdtr.base: %p\n", (uint32_t)gdtr.base);
    printf("gdtr.limit: %p\n", (uint32_t)gdtr.limit);

    printf("\nhexdump of gdt: %p\n", (uint32_t)gdt);
    hexdump((uint32_t)gdt, 64);

    printf("\nhexdump of gdtr: %p\n", &gdtr);
    hexdump((uint32_t)&gdtr, 64);
    
    printf("gdt[2] access: %p\n", gdt[2].access);
}