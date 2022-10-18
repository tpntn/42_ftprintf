/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoas_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:57:00 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/19 00:27:06 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	set_radix(t_params *params)
{
	if (params->conversion == 'u' || params->conversion == 'd')
		return (10);
	if (params->conversion == 'x' || params->conversion == 'X')
		return (16);
	if (params->conversion == 'o' || params->conversion == 'O')
		return (8);
	return (0);
}

long long	set_number(t_params *params, va_list data)
{
	if (params->conversion == 'u' || params->conversion == 'd')
	{
		if (params->length == 1)
			return (va_arg(data, long int));
		if (params->length == 2)
			return (va_arg(data, long long int));
		else
			return (va_arg(data, int));
	}
	else
	{
		if (params->length == 1)
			return (va_arg(data, unsigned long int));
		if (params->length == 2)
			return (va_arg(data, unsigned long long int));
		else
			return (va_arg(data, unsigned int));
	}
}
