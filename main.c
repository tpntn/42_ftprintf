/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:18:25 by tpontine          #+#    #+#             */
/*   Updated: 2022/09/22 15:16:57 by tpontine         ###   ########.fr       */
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
	printf("handling: %c", *c);
	if (is_flag(*c))
		ft_strncat(params->flags, c, 1);
	else if (ft_isdigit(*(c+1)))
		*state = STATE_WIDTH;
	else if (*(c+1) == '.')
		*state = STATE_PRECISION;
	else if (is_length_mod(*(c + 1)))
		*state = STATE_LENGTH;
	else
		*state = STATE_CONVERSION;
}

void	width_handler(const char *c, int *state, t_params *params)
{
	printf("handling: %c", *c);
	if (ft_isdigit(*c))
	{
		params->width *= 10;
		params->width += *c - 48;
		
	}
	if (*c == '.')
		*state = STATE_PRECISION;
	else if (is_length_mod(*(c + 1)))
		*state = STATE_LENGTH;
	else
		*state = STATE_CONVERSION;
}

void	precision_handler(const char *c, int *state, t_params *params)
{
	if (ft_isdigit(*c))
	{
		params->precision *= 10;
		params->precision += *c - 48;
	}
	else if (is_length_mod(*(c+1)))
		*state = STATE_LENGTH;
	else if (!is_length_mod(*(c+1)))
		*state = STATE_CONVERSION;
}

void	length_handler(const char *c, int *state, t_params *params)
{
	if (is_length_mod(*c))
		ft_strncat(params->length, c, 1);
	if (!is_length_mod(*(c + 1))) 
		*state = STATE_CONVERSION;
}

void	conversion_handler(const char *c, int *state, t_params *params)
{
	if (is_conv_mod(*c))
		params->conversion = (char)*c;
	else
		exit(0);
	*state = STATE_NORMAL;
	REMOVE_data_printer(params, *state);
}

void	initialize_params(int *state, t_params *params)
{
	if (*state == STATE_NORMAL)
	{
		params->flags = (char *)malloc(sizeof(char) * 8);
		params->width = 0;
		params->precision = 0;
		params->length = (char *)malloc(sizeof(char) * 3);
		params->conversion = 0;
	}
	if (*state == STATE_CONVERSION)
	{
		free(params->length);
		*state = STATE_NORMAL;
	}
}

void	ft_printf(const char *str, ...)
{
	va_list		data;
	int			state;
	t_params	params;

	state = STATE_NORMAL;
	
	va_start(data, str);
	initialize_params(&state, &params);
	while (*str)
	{
		ft_putchar(*str);
		if (state == STATE_NORMAL)
		{
			if (*str == '%')
				state = STATE_FLAGS;
			else 
				ft_putchar(*str);
		}
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
		REMOVE_data_printer(&params, state);
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

	// ft_printf("g %+-2098.42lu");
	ft_printf("g %+42lu");

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