/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:59:54 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/19 22:07:08 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	if_zero(long long *num)
{
	if (*num < 0)
	{
		*num *= -1;
		return (1);
	}
	return (0);
}

static int	fill_buffer(char **buffer, unsigned long long num, int radix)
{
	uint32_t	rem;
	static char	hexchars[] = "0123456789abcdef";
	int			pos;

	pos = 0;
	while (num > 0)
	{
		rem = num % radix;
		num /= radix;
		*(*buffer + pos++) = hexchars[rem];
	}
	return (pos);
}

int	__ft_itoa(t_params *params, va_list data)
{
	int						radix;
	long long				num;
	int						sign;
	int						pos;
	char					*buffer;

	buffer = ft_strnew(33);
	num = set_number(params, data);
	sign = if_zero(&num);
	radix = set_radix(params);
	pos = fill_buffer(&buffer, (unsigned long long)num, radix);
	if (sign)
		buffer[pos] = '-';
	buffer = ft_strrev(buffer);
	ft_putstr(buffer);
	return (0);
}

void	__ft_itoa_unsigned(t_params *params, va_list data)
{
	int					radix;
	int					pos;
	unsigned long long	num;
	char				*buffer;

	buffer = ft_strnew(33);
	num = set_number(params, data);
	radix = set_radix(params);
	pos = fill_buffer(&buffer, num, radix);
	buffer = ft_strrev(buffer);
	ft_putstr(buffer);
}

int	ft_printf_itoa(t_params *params, va_list data)
{
	if (params->conversion == 'u' || params->conversion == 'd')
		__ft_itoa(params, data);
	else
		__ft_itoa_unsigned(params, data);
	return (0);
}
