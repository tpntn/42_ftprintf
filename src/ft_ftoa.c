/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:02:54 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/20 12:36:02 by tpontine         ###   ########.fr       */
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

void	apply_rounding(char **s, int precision)
{
	if (precision == 0)
	{
		ft_strdel(s);
		*s = ft_strdup("");
	}
	else
	{
		rounder(s, precision, 0);
		ft_memset((*s + precision + 2), 0, ft_strlen(*s) - precision);		
	}
}

void	ftoa_output(t_params *params, char *integer, char *fraction, int sign)
{
	char	*flo;
	int		start;
	int		precision;
	int 	i;
	int		print_len;
	
	// ft_putstr("raw values: ");
	// ft_putstr(integer);
	// ft_putstr(fraction);
	// ft_putchar('\n');

	if (params->precision == -1)
		precision = 6;
	else
		precision = params->precision;
	apply_rounding(&fraction, precision);

	// ft_putstr("raw values: ");
	// ft_putstr(integer);
	// ft_putstr(fraction);
	// ft_putchar('\n');

	start = trim_zeros(integer, 0);
	flo = ft_strjoin(integer + start, fraction + 1);

	// ft_putstr("raw values: ");
	// ft_putstr(flo);
	// ft_putchar('\n');

	i = 0;
	print_len = params->width;
	if (ft_strlen(flo) > params->width)
		print_len = ft_strlen(flo);
	
	
	int flo_start_i;
	int	flo_end_i;

	

	if(params->width > ft_strlen(flo))
		flo_start_i = params->width - ft_strlen(flo);
	
	if (ft_strstr(params->flags,"-") && ft_strstr(params->flags,"+"))
		 flo_start_i = 1;

	flo_end_i = flo_start_i + ft_strlen(flo);

	while (i < print_len)
	{
		if ((ft_strstr(params->flags, "+") || sign) && i == flo_start_i - 1)
		{
			if (sign)
				ft_putchar('-');
			else if (ft_strstr(params->flags, "+"))
				ft_putchar('+');
		}
		else if (i < flo_start_i)
		{
			if (ft_strstr(params->flags, "0"))
				ft_putchar('0');
			else
				ft_putchar(' ');
		}
		else if (i >= flo_start_i)
			ft_putchar(*(flo + i - flo_start_i));
		else if (i )
			ft_putchar('0');
		i++;
	}



	// apply_width(&flo, params);
	// apply_sign(&flo, sign, params);
	// apply_hash(&flo, sign, params);
	// apply_minus(&flo, sign, params);
	// ft_putstr(flo);
	ft_strdel(&flo);
}

void	handler(int exp, char **result_frac, char **result_int)
{
	// ft_putstr("handler called with exp:");
	// ft_putnbr(exp);
	if (exp < 0)
		*result_frac = handle_fraction(exp, *result_frac);
	if (exp >= 0)
		handle_integer(exp, *result_int);
}

static char	*init_frac()
{
	char	*result_frac;

	result_frac = (char *)malloc(sizeof(char) * (4));
	result_frac = ft_strcpy(result_frac, "0.0");
	result_frac[3] = 0;
	return (result_frac);
}

static	void	clear_results(char **result_frac, char **result_int)
{
	ft_strdel(result_frac);
	ft_strdel(result_int);
}	

int	ft_ftoa(t_params *params, va_list data)
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
	if (f == 0)
	{
		ftoa_output(params, result_int, result_frac, 0);
		clear_results(&result_frac, &result_int);
		return (0);
	}
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
	return (0);
}
