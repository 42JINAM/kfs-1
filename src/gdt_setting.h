#ifndef GDT_SETTING_H
# define GDT_SETTING_H

#include <stdint.h>
//selectors 
#define NULL_SELECTOR 0x00
#define KERNEL_CS 0x08
#define KERNEL_DS 0x10
#define USER_CS 0x1B
#define USER_DS 0x23

#define NUM_GDT_ENTRIES 5

//gdt entry
typedef struct __attribute__((packed)) {
    uint16_t limit_low;    // 0-15
    uint16_t base_low;     // 16-31
    uint8_t  base_mid;     // 32
    uint8_t  access;       // 33-40 (type+S+DPL+P)
    uint8_t  gran;         // 41-48 (limit_high+flags)
    uint8_t  base_high;    // 49-56
} gdt_entry_t;  //

//gdtr
typedef struct __attribute__((packed)) s_gdtr
{
	uint16_t	limit;
	uint32_t	base;
}	t_gdtr;

uint64_t	get_kernel_code(void);
uint64_t	get_kernel_data(void);
uint64_t	get_user_code(void);
uint64_t	get_user_data(void);

#endif // !GDT_SETTING_H
