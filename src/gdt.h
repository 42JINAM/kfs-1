#ifndef GDT_H
#define GDT_H

#include <stdint.h>
#include "utils/utils.h"

#define GDT_ADDRESS	0x00000800

// selectors 
#define NULL_SELECTOR 0x00
#define KERNEL_CS 0x08
#define KERNEL_DS 0x10
#define USER_CS 0x1B
#define USER_DS 0x23

#define NUM_GDT_ENTRIES 7

// access
#define GDT_CODE_KERNEL    0x9A  // P=1,DPL=0,S=1,Code/Read
#define GDT_DATA_KERNEL    0x92  // P=1,DPL=0,S=1,Data/Write
#define GDT_CODE_USER      0xFA  // P=1,DPL=3,S=1,Code/Read
#define GDT_DATA_USER      0xF2  // P=1,DPL=3,S=1,Data/Write

// granularity
#define GDT_FLAG_32BIT     0xCF  // G=1(4GB),D=1(32bit),L=0,AVL=0 | meaningless

// limit
#define GDT_LIMIT_4GB      0xFFFFF

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

typedef struct  __attribute__((packed)) gdtr {
    uint16_t limit;
    uint32_t base;
} t_gdtr;

extern t_gdt_entry *gdt;
extern t_gdtr      gdtr;

void gdt_init();
void check_gdt_value();

#endif