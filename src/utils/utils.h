#ifndef UTILS_H
# define UTILS_H

# include "../terminal.h"

# include <stdarg.h>
# include <stdint.h>
# include <stddef.h>

typedef struct stack_frame{
	struct stack_frame* ebp;
	uint32_t	eip;
}	t_stack_frame;

int	    printf(const char *format, ...);
void	printk(char *str, ...);
int	    ft_printf_c(va_list* ap);
int	    ft_printf_s(va_list* ap);
int	    ft_printf_p(va_list* ap);
int	    ft_printf_x(va_list* ap);
int	    ft_printf_xx(va_list* ap);
void    test_printf(void);

void*   memset(void* bufptr, int value, size_t size);
void*   memcpy(void	*restrict dstptr, const void	*restrict srcptr, size_t size);
void	clean_registers(void);
void	print_stack_frame(void);
size_t	strlen(const char	*str);

void    hexdump(uint32_t addr, int limit);

#endif
