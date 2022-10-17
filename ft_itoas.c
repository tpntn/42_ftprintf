/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:59:54 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/17 23:36:37 by tpontine         ###   ########.fr       */
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

void	ft_signed_itoa(t_params *params, va_list data)
{
	int		radix;
	char	*buffer; 
	int		pos;
	static char g_HexChars[] = "0123456789abcdef";
	long long num;

	num = (long long)va_arg(data, long long);
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
	if ((long long)va_arg(data, long long) < 0)
		buffer[pos] = '-';
	buffer = ft_strrev(buffer);
	printf("%s", buffer);
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
	printf("%s", buffer);
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