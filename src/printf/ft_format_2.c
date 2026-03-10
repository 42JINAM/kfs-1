/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:36:26 by yoonsele          #+#    #+#             */
/*   Updated: 2022/12/04 17:25:44 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_hex(unsigned long long nb, char *base)
{
	static int	cnt;
	int			tmp;

	cnt = 0;
	if (nb > 15)
		ft_write_hex(nb / 16, base);
	if (cnt == -1)
		return (-1);
	tmp = write(1, &base[nb % 16], 1);
	if (tmp == -1)
		cnt = -1;
	else
		cnt += tmp;
	return (cnt);
}

int	ft_printf_p(va_list ap)
{
	void	*ptr;
	int		cnt;
	char	*base;

	ptr = (void *)va_arg(ap, void *);
	cnt = 0;
	if (write(1, &"0", 1) == -1)
		return (-1);
	cnt++;
	if (write(1, &"x", 1) == -1)
		return (-1);
	cnt++;
	base = "0123456789abcdef";
	cnt += ft_write_hex((unsigned long long)ptr, base);
	return (cnt);
}

int	ft_printf_x(va_list ap)
{
	unsigned int	x;
	char			*base;

	x = va_arg(ap, unsigned int);
	base = "0123456789abcdef";
	return (ft_write_hex(x, base));
}

int	ft_printf_xx(va_list ap)
{
	unsigned int	xx;
	char			*base;

	xx = va_arg(ap, unsigned int);
	base = "0123456789ABCDEF";
	return (ft_write_hex(xx, base));
}
