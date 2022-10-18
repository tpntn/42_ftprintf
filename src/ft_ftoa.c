/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:02:54 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/19 00:42:52 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	trim_zeros(char *integer)
{
	int	i;

	i = 0;
	while (integer[i] == '0')
		i++;
	return (i);
}

void	ftoa_output(t_params *params, char *integer, char *fraction, int sign)
{
	char	*flo;
	int		start;
	
	start = trim_zeros(integer);
	flo = ft_strjoin(integer + start, fraction + 1);
	ft_putstr(flo);

	params->id = 0;
	sign = 0;
	// int	a;
	// int	i;
	// int	c;

	// a = 0;
	// if (sign == 1)
	// 	ft_putchar('-');
	// while (*(integer + a) == '0' && a < 39)
	// 	a++;
	// while (*(integer + a))
	// 	ft_putchar(*(integer + a++));
	// i = 0;
	// c = 1;
	// rounder(&fraction, params->precision, 0);
	// while (c < (int)ft_strlen(fraction) && c <= params->precision + 1)
	// 	ft_putchar(*(fraction + c++));
	// while (c++ <= params->precision + 1)
	// 	ft_putchar('0');
}

void	handler(int exp, char **result_frac, char **result_int)
{
	if (exp < 0)
		*result_frac = handle_fraction(exp, *result_frac);
	if (exp >= 0)
		handle_integer(exp, *result_int);
}

static char	*init_frac(void)
{
	char	*result_frac;

	result_frac = (char *)malloc(sizeof(char) * 4);
	result_frac = ft_strcpy(result_frac, "0.0");
	return (result_frac);
}

static	void	clear_results(char **result_frac, char **result_int)
{
	ft_strdel(result_frac);
	ft_strdel(result_int);
}	

void	ft_ftoa(t_params *params, va_list data)
{
	int		i;
	int		exp;
	char	*result_frac;
	char	*result_int;
	float	f;

	f = (float)va_arg(data, double);
	exp = ret_exp(f);
	result_frac = init_frac();
	result_int = malloc_and_setzero(40);
	i = 22;
	handler(exp, &result_frac, &result_int);
	exp--;
	while (i >= 0)
	{
		if ((*((int *)&f) >> i--) & 1)
			handler(exp, &result_frac, &result_int);
		exp--;
	}
	if (((*((int *)&f) >> 31) & 1))
		ftoa_output(params, result_int, result_frac, 1);
	else
		ftoa_output(params, result_int, result_frac, 0);
	clear_results(&result_frac, &result_int);
}
