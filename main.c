/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:18:25 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/17 09:56:09 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// gcc func_pointers.c -I Libft/ -L libft -lft

void	REMOVE_data_printer(t_params *params, int state)
{
	printf("\n\nflags:\t\t%s\n", params->flags);
	printf("width:\t\t%d\n", params->width);
	printf("precision:\t%d\n", params->precision);
	printf("length:\t\t%s\n", params->length);
	printf("conversion:\t%c\n", params->conversion);

	printf("state: %d\n\n", state);
}

static t_type types[] = {
	{'f', ft_ftoa}
	// {'s', ft_putstr}
};

int	is_type_specifier(char str)
{
	const char *types = "csdioxXuFfeEaAgGnp";
	while (*types)
	{
		if (*types == str)
			return (1);
		types++;
	}
	return (0);
}

int		is_flag(char c)
{
	const char flags[] = "-+ #0";
	int i;

	i = 0;
	while (flags[i])
	{
		if (flags[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		is_length_mod(char c)
{
	const char flags[] = "hlqLjzZt";
	int i;

	i = 0;
	while (flags[i])
	{
		if (flags[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		is_conv_mod(char c)
{
	const char flags[] = "diouxXeEfFgGaAcsCSpnm%";
	int i;

	i = 0;
	while (flags[i])
	{
		if (flags[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	flags_handler(const char *c, int *state, t_params *params, va_list data)
{
	if (is_flag(*c))
		ft_strncat(params->flags, c, 1);
	else
	{
		*state = STATE_WIDTH;
		width_handler(c, state, params, data);
	}
}

void	width_handler(const char *c, int *state, t_params *params, va_list data)
{
	if (ft_isdigit(*c))
	{
		params->width *= 10;
		params->width += *c - 48;
	}
	else if (*c == '.')
		*state = STATE_PRECISION;
	else if (*c != '.')
		length_handler(c, state, params, data);
}

void	precision_handler(const char *c, int *state, t_params *params, va_list data)
{
	if (ft_isdigit(*c))
	{
		params->precision *= 10;
		params->precision += *c - 48;
	}
	else
		length_handler(c, state, params, data);
}

void	length_handler(const char *c, int *state, t_params *params, va_list data)
{
	if (is_length_mod(*c))
		ft_strncat(params->length, c, 1);
	else
		conv_handl(c, state, params, data);
}

void	check_params(t_params **params)
{
	if ((*params)->precision == 0)
		(*params)->precision = 6;
}

void	conv_handl(const char *c, int *state, t_params *params, va_list data)
{
	int	i;
	if (is_conv_mod(*c))
		params->conversion = (char)*c;
	check_params(&params);
	i = 0;
	while (i < 1)
	{
		if (types[i].id == *c)
			types[i].func(params, data);
		i++;
	}
	*state = STATE_NORMAL;
	clear_params(params);
	initialize_params(params);
}

void	normal_handler(const char *c, int *state)
{
	if (*c == '%')
		*state = STATE_FLAGS;
	else 
		ft_putchar(*c);
}

void	ft_printf(const char *str, ...)
{
	va_list		data;
	int			state;
	t_params	params;

	state = STATE_NORMAL;
	initialize_params(&params);
	va_start(data, str);
	
	while (*str)
	{
		if (state == STATE_NORMAL)
			normal_handler(str, &state);
		else if (state == STATE_FLAGS)
			flags_handler(str, &state, &params, data);
		else if (state == STATE_WIDTH)
			width_handler(str, &state, &params, data);
		else if (state == STATE_PRECISION)
			precision_handler(str, &state, &params, data);
		else if (state == STATE_LENGTH)
			length_handler(str, &state, &params, data);
		else if (state == STATE_CONVERSION)
			conv_handl(str, &state, &params, data);
		str++;
	}
	va_end(data);
	clear_params(&params);
}

int main()
{
	// float f = __FLT_MAX__;
	// float f = 100.0;
	// printf("%f\n",f);
	// printf("%#f\n",f);
	// printf("%020f\n",f);

	float f = 0.1;
	printf("%.1f\n",f);
	ft_printf("%.1f\n",f);
	
	printf("%.2f\n",f);
	ft_printf("%.2f\n",f);

	printf("%.3f\n",f);
	ft_printf("%.3f\n",f);

	printf("%.4f\n",f);
	ft_printf("%.4f\n",f);

	printf("%.5f\n",f);
	ft_printf("%.5f\n",f);

	printf("%.6f\n",f);
	ft_printf("%.6f\n",f);

	printf("%.7f\n",f);
	ft_printf("%.7f\n",f);

	printf("%.8f\n",f);
	ft_printf("%.8f\n",f);

	printf("%.9f\n",f);
	ft_printf("%.9f\n",f);

	printf("%.10f\n",f);
	ft_printf("%.10f\n",f);

	printf("%.11f\n",f);
	ft_printf("%.11f\n",f);

	printf("%.25f\n",f);
	ft_printf("%.25f\n",f);

	printf("%.35f\n",f);
	ft_printf("%.35f\n",f);

	printf("%.45f\n",f);
	ft_printf("%.45f\n",f);

	printf("%.46f\n",f);
	ft_printf("%.46f\n",f);

	printf("%.101f\n",f);
	ft_printf("%.101f\n",f);
	// float f = __FLT_MIN__;
	// long double d = __DBL_MIN__;
	// ft_printf("ft_printf: __FLT_MIN__:\t%.126f\n",f);
	// printf("printf: __FLT_MIN__:\t%.150lf\n",f);
	// printf("printf: __DBL_MIN__:\t%Lf\n",d);
	// ft_printf("This is \n amasing %+- 123.42lld asd");
	// ft_printf("g %+42lu");

	
	return (0);
}