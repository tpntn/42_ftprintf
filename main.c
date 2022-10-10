/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:18:25 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/10 13:42:18 by tpontine         ###   ########.fr       */
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

void	flags_handler(const char *c, int *state, t_params *params)
{
	if (is_flag(*c))
		ft_strncat(params->flags, c, 1);
	else
	{
		*state = STATE_WIDTH;
		width_handler(c, state, params);
	}
}

void	width_handler(const char *c, int *state, t_params *params)
{
	if (ft_isdigit(*c))
	{
		params->width *= 10;
		params->width += *c - 48;
	}
	else if (*c == '.')
		*state = STATE_PRECISION;
}

void	precision_handler(const char *c, int *state, t_params *params)
{
	if (ft_isdigit(*c))
	{
		params->precision *= 10;
		params->precision += *c - 48;
	}
	else
		length_handler(c, state, params);
}

void	length_handler(const char *c, int *state, t_params *params)
{
	if (is_length_mod(*c))
		ft_strncat(params->length, c, 1);
	else
		conversion_handler(c, state, params);
}

void	conversion_handler(const char *c, int *state, t_params *params)
{
	if (is_conv_mod(*c))
		params->conversion = (char)*c;
	// else
	// 	exit(0);
	*state = STATE_NORMAL;
	REMOVE_data_printer(params, *state);
	clear_params(params);
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
	va_start(data, str);
	initialize_params(&params);
	
	while (*str)
	{
		if (state == STATE_NORMAL)
			normal_handler(str, &state);
		else if (state == STATE_FLAGS)
			flags_handler(str, &state, &params);
		else if (state == STATE_WIDTH)
			width_handler(str, &state, &params);
		else if (state == STATE_PRECISION)
			precision_handler(str, &state, &params);
		else if (state == STATE_LENGTH)
			length_handler(str, &state, &params);
		else if (state == STATE_CONVERSION)
			conversion_handler(str, &state, &params);
		str++;
	}
	va_end(data);
}

int main()
{
	// float f = 104857.601562;
	// float f = 1.17549435082e-38; //ei toimi
	float f = 0.1;
	// float f = 1.0e38; //lähellä maksia???
	// float f = 1.5e-37; //tämä on viimeinen joka toimii.... -38 ei toimi enää
	// float f = -1.0e-37;

	// printf("%.146f\n",f);
	// ft_ftoa(f);

	ft_printf("This is \n amasing %+- 123.42lld what %30d do you %20d think?");
	// ft_printf("This is \n amasing %+- 123.42lld asd");
	// ft_printf("g %+42lu");

	// int state = 0;
	// t_params params;
	// initialize_params(&state, &params);

	// const char *s = "200";
	// while (*s)
	// {
	// 	width_handler(s, &state, &params);
	// 	REMOVE_data_printer(&params, state);
	// 	s++;
	// }
	
	
	return (0);
}