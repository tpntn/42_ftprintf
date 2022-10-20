/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:02:54 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/20 15:11:26 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	trim_zeros(char *s, int i)
{
	while (s[i] == '0' && s[i + 1] != 0)
		i++;
	return (i);
}

int		print_len(char *s, t_params *params, int sign)
{
	int	len;

	len = params->width;
	if (params->precision > params->width)
		len = params->precision;
	if ((int)ft_strlen(s) > len)
		len = (int)ft_strlen(s);
	if (ft_strstr(params->flags, "+") || sign)
		len++;
	return (len);
}

void	apply_rounding(char **s, int precision)
{
	char *temp;

	if (precision == 0)
	{
		ft_strdel(s);
		*s = ft_strdup("");
	}
	else
	{
		rounder(s, precision, 0);
		temp = ft_strnew(precision + 2);
		temp = ft_strncpy(temp, *s, precision + 2);
		*s = ft_strdup(temp);
		ft_strdel(&temp);
	}
}

void	ftoa_output(t_params *params, char *integer, char *fraction, int sign)
{
	char	*flo;
	int		start;
	int		precision;
	int		pt_len;
	
	if (params->precision == -1)
		precision = 6;
	else
		precision = params->precision;
	apply_rounding(&fraction, precision);

	

	start = trim_zeros(integer, 0);
	flo = ft_strjoin(integer + start, fraction + 1);
	pt_len = print_len(flo, params, sign);
	apply_width(&flo, params);
	apply_sign(&flo, sign, params);
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
