/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:57:46 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/19 22:06:38 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puts(t_params *params, va_list data)
{
	if (params->conversion == 's')
		ft_putstr(va_arg(data, char *));
	return (0);
}

int	ft_putc(t_params *params, va_list data)
{
	if (params->conversion == 'c')
		ft_putchar(va_arg(data, int));
	return (0);
}

int	ft_ptr(t_params *params, va_list data)
{
	if (params->conversion == 'p')
	{
		params->length = 1;
		params->precision = 10;
		params->conversion = 'x';
		ft_putstr("0x");
		__ft_itoa_unsigned(params, data);
	}
	return (0);
}
