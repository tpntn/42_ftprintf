/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:59:54 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/18 13:50:10 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_printf.h"

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
	if (params->precision == "l")
		return (va_arg(data, long int));
	if (params->precision == "ll")
		return (va_arg(data, long long int));
}

void	__ft_itoa(t_params *params, va_list data)
{
	int						radix;
	char					*buffer; 
	int						pos;
	static char 			g_HexChars[] = "0123456789abcdef";
	long long				num;

	ft_putstr("ft_signed_itoa called");
	num = set_type(t_params *params, va_list data);
	buffer= (char*)malloc(sizeof(char) * 33);
	ft_memset(buffer,0,33);
	if (num < 0)
		num *= -1;
	pos = 0;
	radix = set_radix(params);
	while (num > 0)
	{
		uint32_t rem =  num % radix;
		num  /= radix;
		buffer[pos++] = g_HexChars[rem];
	}
	if ((long)va_arg(data, long) < 0)
		buffer[pos] = '-';
	buffer = ft_strrev(buffer);
	ft_putstr(buffer);
}

void	ft_printf_itoa(t_params *params, va_list data)
{
	if (params->conversion == 'u' || params->conversion == 'd')
					__ft_itoa(params, data);	
	if (params->conversion == 'x' || params->conversion == 'X')
	{
		;
	}	
	if (params->conversion == 'o' || params->conversion == 'O')
	{
		;
	}
}

void	ft_unsigned_itoa(t_params *params, va_list data)
{
	int		radix;
	char	*buffer; 
	int		pos;
	static char g_HexChars[] = "0123456789abcdef";
	unsigned long long num;

	buffer= (char*)malloc(sizeof(char) * 33);
	ft_memset(buffer,0,33);
	num = (unsigned long long)va_arg(data, unsigned long long);
	pos = 0;
	radix = set_radix(params);
	while (num > 0)
	{
		uint32_t rem =  num % radix;
		num  /= radix;
		buffer[pos++] = g_HexChars[rem];
	}
	buffer = ft_strrev(buffer);
	ft_putstr(buffer);
}

// int	main()
// {
// 	t_params params = {0,"",3,0,"ll",'u'};

// 	unsigned long long i = ULLONG_MAX;
// 	printf("%s\n",ft_unsig(&i, &params));
// 	printf("%llu\n", ULLONG_MAX);
	
// 	int a = -123;
// 	params.conversion = 'd';
// 	printf("%s\n",ft_printf_print_int(&a, &params));
// 	printf("%d\n", a);

// 	return (0);
// }