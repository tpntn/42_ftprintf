/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:47:37 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/20 21:30:18 by tpontine         ###   ########.fr       */
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

void	handle_fraction(int exp, char **result_frac)
{
	size_t	len_f;
	size_t	len_m;
	char	*new;
	char	*m;
	char	*addition;
	char	*temp;

	temp = ft_strdup(*result_frac);
	free(*result_frac);
	m = count_fraction(exp);
	len_f = ft_strlen(temp);
	len_m = ft_strlen(m);
	addition = malloc_and_setzero(len_m - len_f + 1);
	new = ft_strjoin(temp, addition);
	adder(&new, m);
	free(m);
	free(addition);
	*result_frac = ft_strdup(new);
	free(new);
	free(temp);
}

void	handle_integer(int exp, char **result_int)
{
	char	*m;

	m = count_integer(exp);
	adder(result_int, m);
	ft_strdel(&m);
}
