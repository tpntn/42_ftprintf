/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:47:37 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/19 23:45:13 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// mallocs size + 1, set all values to '0' char and terminating NULL char
char	*malloc_and_setzero(int size)
{
	char	*s;

	s = (char *)malloc(sizeof(char) * size + 1);
	if (!s)
		return (0);
	*(s + size) = 0;
	size--;
	while (size)
		*(s + size--) = '0';
	*s = '0';
	return (s);
}

//counts and returns the value of fraction based exponent given
char	*count_fraction(int exp)
{
	char	*result;
	int		c;

	if (exp == 0)
		return ("1.0");
	if (exp < 0)
		exp *= -1;
	result = malloc_and_setzero(exp + 2);
	result[exp + 1] = '1';
	c = 0;
	while (c < exp)
	{
		multiplyer(&result, 5, exp + 2);
		c++;
	}
	result[1] = '.';
	return (result);
}

//count the integer based on exp
char	*count_integer(int exp)
{
	int		i;
	char	*result;

	result = malloc_and_setzero(40);
	result[39] = '1';
	i = 0;
	while (i < exp)
	{
		multiplyer(&result, 2, 40);
		i++;
	}
	return (result);
}

char	*handle_fraction(int exp, char *result_frac)
{
	size_t	len_f;
	size_t	len_m;
	char	*new;
	char	*m;
	char	*addition;

	m = count_fraction(exp);
	len_f = ft_strlen(result_frac);
	len_m = ft_strlen(m);
	addition = malloc_and_setzero(len_m - len_f + 1);
	new = ft_strjoin(result_frac, addition);
	ft_putstr(new);
	ft_putchar('\n');
	adder(&new, m);
	ft_putstr(new);
	ft_strdel(&m);
	ft_strdel(&addition);
	ft_strdel(&result_frac);
	return (new);
}

void	handle_integer(int exp, char *result_int)
{
	char	*m;

	m = count_integer(exp);
	ft_putstr("m based on exp: ");
	ft_putstr(m);
	ft_putstr("result int: ");
	ft_putstr(result_int);
	ft_putchar('\n');
	adder(&result_int, m);
	ft_putstr("result int aft adder: ");
	ft_putstr(result_int);
	ft_putchar('\n');
	ft_strdel(&m);
}
