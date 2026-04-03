#include "utils.h"

void	clean_registers(void)
{
	asm volatile ("xorl %eax, %eax \n\t"
					"xorl %ebx, %ebx \n\t"
					"xorl %ecx, %ecx \n\t"
					"xorl %edx, %edx \n\t"
					"xorl %esi, %esi \n\t"
					"xorl %edi, %edi \n\t"
					"xorl %ebp, %ebp \n\t"
					"mov %ds, %ax \n\t"
					"mov %es, %ax \n\t"
					"mov %fs, %ax \n\t"
					"mov %gs, %ax \n\t"
					);
}

/// @brief 
/// @param  
void	print_stack_frame(void)
{
	t_stack_frame* frame;

	asm volatile("mov %%ebp, %0": "=r"(frame));
	printf("first ebp %p\n", frame);
	while (frame)
	{
		printf("call addr: %p\n", frame->eip);
		frame = frame->ebp;
	}
}
