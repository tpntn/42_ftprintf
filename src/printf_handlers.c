/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:08:05 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/19 18:50:46 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	{
		*state = STATE_LENGTH;
		len_handler(c, state, params, data);
	}
}

void	prec_handler(const char *c, int *state, t_params *params, va_list data)
{
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
