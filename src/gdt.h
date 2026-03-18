#ifndef GDT_H
#define GDT_H

#include <stdint.h>

#define GDT_ADDRESS	0x00000800

// uint8_t	1 byte
// uint16_t	2 bytes
// uint32_t	4 bytes

typedef struct  __attribute__((packed)) gdt_entry {
  uint16_t limit_low; 
  uint16_t base_low; 
  uint8_t  base_middle; 
  uint8_t  access; 
  uint8_t  granularity; 
  uint8_t  base_high; 
} t_gdt_entry;

typedef struct  __attribute__((packed)) gdt_ptr {
    uint16_t limit;
    uint32_t base;
} t_gdt_ptr;

extern t_gdt_entry *gdt;
extern t_gdt_ptr   *gp;

void gdt_init();
void check_gdt_value();

#endif