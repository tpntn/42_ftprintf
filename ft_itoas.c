/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:59:54 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/18 15:34:57 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	set_radix(t_params *params)
{
	if (params->conversion == 'u' || params->conversion == 'd')
		return (10);
	if (params->conversion == 'x' || params->conversion == 'X')
		return (16);
	if (params->conversion == 'o' || params->conversion == 'O')
		return (8);
	return (0);
}

static long long	set_number(t_params *params, va_list data)
{
	if (params->conversion == 'u' || params->conversion == 'd')
	{
		if (params->length == 1)
			return (va_arg(data, long int));
		if (params->length == 2)
			return (va_arg(data, long long int));
		else
			return (va_arg(data, int));
	}
	else
	{
		if (params->length == 1)
			return (va_arg(data, unsigned long int));
		if (params->length == 2)
			return (va_arg(data, unsigned long long int));
		else
			return (va_arg(data, unsigned int));
	}
	
}

void	__ft_itoa(t_params *params, va_list data)
{
	int						radix;
	char					*buffer; 
	int						pos;
	static char 			g_HexChars[] = "0123456789abcdef";
	long long				num;
	int						sign;
	
	num = set_number(params, data);
	buffer = (char*)malloc(sizeof(char) * 33);
	ft_memset(buffer,0,33);
	sign = 0;
	if (num < 0)
	{
		num *= -1;
		sign = 1;
	}
	pos = 0;
	radix = set_radix(params);
	while (num > 0)
	{
		uint32_t rem =  num % radix;
		num /= radix;
		buffer[pos++] = g_HexChars[rem];
	}
	if (sign)
		buffer[pos] = '-';
	buffer = ft_strrev(buffer);
	ft_putstr(buffer);
}

void	__ft_itoa_unsigned(t_params *params, va_list data)
{
	int		radix;
	char	*buffer; 
	int		pos;
	static char g_HexChars[] = "0123456789abcdef";
	unsigned long long num;

	buffer = (char*)malloc(sizeof(char) * 33);
	ft_memset(buffer,0,33);
	num = set_number(params, data);
	pos = 0;
	radix = set_radix(params);
	//HOW TO HANDLE ZERO
	while (num > 0)
	{
		uint32_t rem =  num % radix;
		num  /= radix;
		buffer[pos++] = g_HexChars[rem];
	}
	buffer = ft_strrev(buffer);
	ft_putstr(buffer);
}

void	ft_printf_itoa(t_params *params, va_list data)
{
	if (params->conversion == 'u' || params->conversion == 'd')
		__ft_itoa(params, data);
	else
		__ft_itoa_unsigned(params, data);
}