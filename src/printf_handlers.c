/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:08:05 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/19 16:39:04 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flags_handler(const char *c, int *state, t_params *params, va_list data)
{
	// ft_putstr("flags_handler\n");
	// ft_putchar(*c);
	// ft_putchar(*state + 48);
	// ft_putstr("=======================\nid: ");
	// ft_putnbr(params->id);
	// ft_putstr("\nflags: ");
	// ft_putstr(params->flags);
	// ft_putstr("\nwidth: ");
	// ft_putnbr(params->width);
	// ft_putstr("\nprec: ");
	// ft_putnbr(params->precision);
	// ft_putstr("\nlen: ");
	// ft_putnbr(params->length);
	// ft_putstr("\nconv: ");
	// ft_putchar(params->conversion);
	// ft_putstr("\n\n\n");
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
	// ft_putstr("width_handler\n");
	// ft_putchar(*c);
	// ft_putchar(*state + 48);
	// ft_putstr("=======================\nid: ");
	// ft_putnbr(params->id);
	// ft_putstr("\nflags: ");
	// ft_putstr(params->flags);
	// ft_putstr("\nwidth: ");
	// ft_putnbr(params->width);
	// ft_putstr("\nprec: ");
	// ft_putnbr(params->precision);
	// ft_putstr("\nlen: ");
	// ft_putnbr(params->length);
	// ft_putstr("\nconv: ");
	// ft_putchar(params->conversion);
	// ft_putstr("\n\n\n");
	if (ft_isdigit(*c))
	{
		params->width *= 10;
		params->width += *c - 48;
	}
	else if (*c == '.')
		*state = STATE_PRECISION;
	else if (*c != '.')
	{
		*state = STATE_LENGTH;
		len_handler(c, state, params, data);
	}
}

void	prec_handler(const char *c, int *state, t_params *params, va_list data)
{
	// ft_putstr("prec_handler\n");
	// ft_putchar(*c);
	// ft_putchar(*state + 48);
	// ft_putstr("=======================\nid: ");
	// ft_putnbr(params->id);
	// ft_putstr("\nflags: ");
	// ft_putstr(params->flags);
	// ft_putstr("\nwidth: ");
	// ft_putnbr(params->width);
	// ft_putstr("\nprec: ");
	// ft_putnbr(params->precision);
	// ft_putstr("\nlen: ");
	// ft_putnbr(params->length);
	// ft_putstr("\nconv: ");
	// ft_putchar(params->conversion);
	// ft_putstr("\n\n\n");
	if (ft_isdigit(*c))
	{
		if (params->precision == -1)
			params->precision = 0;
		params->precision *= 10;
		params->precision += *c - 48;
	}
	else
	{
		*state = STATE_LENGTH;
		len_handler(c, state, params, data);
	}
		
}

void	len_handler(const char *c, int *state, t_params *params, va_list data)
{
	// ft_putstr("len_handler\n");
	// ft_putchar(*c);
	// ft_putchar(*state + 48);
	// ft_putstr("=======================\nid: ");
	// ft_putnbr(params->id);
	// ft_putstr("\nflags: ");
	// ft_putstr(params->flags);
	// ft_putstr("\nwidth: ");
	// ft_putnbr(params->width);
	// ft_putstr("\nprec: ");
	// ft_putnbr(params->precision);
	// ft_putstr("\nlen: ");
	// ft_putnbr(params->length);
	// ft_putstr("\nconv: ");
	// ft_putchar(params->conversion);
	// ft_putstr("\n\n\n");
	if (is_length_mod(*c))
	{
		if (*c == 'l')
			params->length++;
		if (*c == 's')
			params->length--;
	}
	else
	{
		*state = STATE_CONVERSION;
		conv_handl(c, state, params, data);
	}
		
}

void	normal_handler(const char *c, int *state)
{
	if (*c == '%')
		*state = STATE_FLAGS;
	else
		ft_putchar(*c);
}
