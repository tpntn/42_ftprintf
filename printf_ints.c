/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_ints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:59:54 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/17 17:15:31 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_printf.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include "Libft/libft.h"

static int	ft_nbr_len(long long nb)
{
	int	i;

	i = 1;
	if (nb < 0)
	{
		i++;
		nb *= -1;
	}
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static long	ft_div(int len)
{
	long	i;

	i = 1;
	if (len == 1)
		return (1);
	while (len > 1)
	{
		i *= 10;
		len--;
	}
	return (i);
}

char	*ft_dtoa(long long n)
{
	int		i;
	int		len;
	int		len2;
	char	*result;

	i = 0;
	len = ft_nbr_len(n);
	len2 = len;
	result = (char *)malloc(sizeof(char) * ((size_t)len + 1));
	if (!result)
		return (NULL);
	if (n == -9223372036854775807)
		return (ft_strdup("-9223372036854775807"));
	if (n < 0)
	{
		n *= -1;
		result[0] = '-';
		i++;
		len--;
	}
	while (i < len2)
		result[i++] = ((n / ft_div(len--)) % 10) + 48;
	result[i] = '\0';
	return (result);
}

char	*ft_ulltoa(unsigned long long n)
{
	int		i;
	int		len;
	int		len2;
	char	*result;

	i = 0;
	len = ft_nbr_len(n);
	len2 = len;
	result = (char *)malloc(sizeof(char) * ((size_t)len + 1));
	if (!result)
		return (NULL);
	while (i < len2)
		result[i++] = ((n / ft_div(len--)) % 10) + 48;
	result[i] = '\0';
	return (result);
}

void	parse_unsigned_bits(void *nb)
{
	int	*p;
	size_t	size;

	p = (int*)&nb;
	size = sizeof(nb);
	printf("%zu\n", size);
	size *= 8;
	while(size)
	{
		printf("%d ", ((*p >> size) & 1));
		size--;
	}
}

void printBits(unsigned long long num)
{
   for (unsigned long bit = 0; bit < (sizeof(unsigned long long) * 8); bit++)
   {
      printf("%llu ", num & 1);
      num = num >> 1;
   }
   printf("\n");
}

char	*to_ascii(unsigned long long number, int radix)
{
	char *buffer = (char*)malloc(sizeof(char) * 33);
	ft_memset(buffer,0,33);
	int pos = 0;
	const char g_HexChars[] = "0123456789abcdef";
	do 
    {
        uint32_t rem =  number % radix;   
		number /= radix;    
        buffer[pos++] = g_HexChars[rem];
    } while (number > 0);

	buffer = ft_strrev(buffer);
	return (buffer);
}

int	main()
{
	// long long l = 9223372036854775807;
	unsigned long long int longlong = __LONG_LONG_MAX__;
	// unsigned long long int longlong = 512;
	
	// int len = ft_nbr_len(l);
	// printf("%s\n", ft_dtoa(l));
	// printf("%s\n", ft_ulltoa(longlong * 2));
	// printf("%llu\n", l * 2);
	// parse_unsigned_bits(&longlong);
	// printBits(512);
	// printBits(longlong);
	printf("%s\n",to_ascii(522,10));
	printf("%s\n",to_ascii(522,16));
	printf("%s\n",to_ascii(longlong*2 ,16));
	printf("%llx\n", longlong*2);


	// printf("%zu\n", sizeof(longlong));
	
	
	return (0);
}