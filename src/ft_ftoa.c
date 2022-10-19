/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:02:54 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/19 16:41:25 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	trim_zeros(char *s, int i)
{
	while (s[i] == '0' && s[i + 1] != 0)
		i++;
	return (i);
}

// 00000123.123
// prec = 3;
// len = 7;
// if width = 12; => nollia tulostuu 12 - 7

void	ftoa_output(t_params *params, char *integer, char *fraction, int sign)
{
	char	*flo;
	int		start;
	int		precision;

	if (params->precision == -1)
		precision = 6;
	else
		precision = params->precision;
	rounder(&fraction, precision, 0);
	ft_memset((fraction + params->precision + 2), 0, ft_strlen(fraction) - params->precision);
	start = trim_zeros(integer, 0);
	flo = ft_strjoin(integer + start, fraction + 1);
	apply_width(&flo, params);	
	apply_sign(&flo, sign, params);
	apply_hash(&flo, sign, params);
	apply_minus(&flo, sign, params);
	ft_putstr(flo);
	ft_strdel(&flo);
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
