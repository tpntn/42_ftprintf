/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:18:25 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/19 16:50:14 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// check if global variables are allowed
static t_type	g_types[] = {
{'f', ft_ftoa},
{'i', ft_printf_itoa},
{'d', ft_printf_itoa},
{'x', ft_printf_itoa},
{'X', ft_printf_itoa},
{'u', ft_printf_itoa},
{'o', ft_printf_itoa},
{'s', ft_puts},
{'c', ft_putc},
{'p', ft_ptr}
};

void	conv_handl(const char *c, int *state, t_params *params, va_list data)
{
	int	i;
	
	if (is_conv_mod(*c))
		params->conversion = (char)*c;
	check_params(&params);	
	i = 0;
	if (params->conversion == '%')
		ft_putchar('%');
	else
	{
		while (i < 10)
		{	
		if (g_types[i].id == *c)
			g_types[i].func(params, data);
		i++;
		}
	}
	
	*state = STATE_NORMAL;	
	clear_params(params);
	initialize_params(params);
}

int	ft_printf(const char *str, ...)
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
			prec_handler(str, &state, &params, data);
		else if (state == STATE_LENGTH)
			len_handler(str, &state, &params, data);
		else if (state == STATE_CONVERSION)
			conv_handl(str, &state, &params, data);
		str++;
	}
	va_end(data);
	clear_params(&params);
	return (0);
}
