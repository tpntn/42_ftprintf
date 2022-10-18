/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:02:54 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/18 22:08:09 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	multiplyer(char **s, int multiplyer, int len)
{
	int		i;
	char	digit;
	char	next;

	next = 0;
	i = len - 1;
	while (i >= 0)
	{
		digit = *(*s + i) - 48;
		digit *= multiplyer;
		digit += next;
		next = 0;
		if (digit > 9)
		{
			next = digit / 10;
			digit %= 10;
			digit += 48;
			*(*s + i) = digit;
		}
		else
		{
			digit += 48;
			*(*s + i) = digit;
		}
		i--;
	}
}

int	to_pwr(int exp, int base)
{
	int	ret;
	int	i;

	ret = base;
	if (exp == 0)
		return (1);
	i = exp - 1;
	while (i--)
		ret *= base;
	return (ret);
}

int	ret_exp(float f)
{
	int	exp;
	int	e;
	int	i;
	int	*p;

	p = (int *)&f;
	i = 23;
	exp = 0;
	e = 0;
	while (i < 31)
		exp += ((*p >> i++) & 1) * to_pwr(e++, 2);
	exp += -127;
	return (exp);
}

void	adder(char **addto, char *num)
{
	int	i;

	i = 0;
	while (*(num + i))
		i++;
	i--;
	while (*(num + i) != '.' && i)
	{
		if (*(*addto + i) + (*(num + i) - 48) > '9')
		{
			*(*addto + i - 1) += 1;
			*(*addto + i) += *(num + i) - 10 - 48;
		}
		else
			*(*addto + i) += *(num + i) - 48;
		i--;
	}
}

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
	adder(&new, m);
	ft_strdel(&m);
	ft_strdel(&addition);
	ft_strdel(&result_frac);
	return (new);
}

void	handle_integer(int exp, char *result_int)
{
	char	*m;

	m = count_integer(exp);
	adder(&result_int, m);
	ft_strdel(&m);
}

int	rounder(char **fraction, int precision, int memo)
{
	if ((precision > (int)ft_strlen(*fraction) - 2))
		return (0);
	if ((*fraction)[precision + 2] < '5' && !memo)
		return (0);
	if (memo)
	{
		if ((*fraction)[precision + 1] + 1 > '9')
		{
			(*fraction)[precision + 1] = '0';
			return (rounder(fraction, precision - 1, 1));
		}
		else
			(*fraction)[precision + 1]++;
	}
	if ((*fraction)[precision + 2] >= '5' && !memo)
	{
		if ((*fraction)[precision + 1] + 1 > '9')
		{
			(*fraction)[precision + 1] = '0';
			return (rounder(fraction, precision - 1, 1));
		}
		else
			(*fraction)[precision + 1]++;
	}
	return (0);
}

void	printer(t_params *params, char *integer, char *fraction, int sign)
{
	int	a;
	int	i;
	int	c;

	a = 0;
	if (sign == 1)
		ft_putchar('-');
	while (*(integer + a) == '0' && a < 39)
		a++;
	while (*(integer + a))
		ft_putchar(*(integer + a++));
	i = 0;
	c = 1;
	rounder(&fraction, params->precision, 0);
	while (c < (int)ft_strlen(fraction) && c <= params->precision + 1)
		ft_putchar(*(fraction + c++));
	while (c++ <= params->precision + 1)
		ft_putchar('0');
}

void	handler(int exp, char **result_frac, char **result_int)
{
	if (exp < 0)
		*result_frac = handle_fraction(exp, *result_frac);
	if (exp >= 0)
		handle_integer(exp, *result_int);
}

void	ft_ftoa(t_params *params, va_list data)
{
	int		*p;
	int		i;
	int		exp;
	char	*result_frac;
	char	*result_int;

	float f = (float)va_arg(data, double);
	exp = ret_exp(f);
	result_frac = (char *)malloc(sizeof(char) * 4);
	result_frac = ft_strcpy(result_frac, "0.0");
	result_int = malloc_and_setzero(40);
	p = (int *)&f;
	i = 22;
	handler(exp,&result_frac, &result_int);
	exp--;
	while (i >= 0)
	{
		if ((*p >> i) & 1)
			handler(exp, &result_frac, &result_int);
		exp--;
		i--;
	}
	if (((*p >> 31) & 1))
		printer(params, result_int, result_frac, 1);
	else
		printer(params, result_int, result_frac, 0);
	ft_strdel(&result_frac);
	ft_strdel(&result_int);
}