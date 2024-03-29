/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:59:55 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/20 18:23:26 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	initialize_params(t_params *params)
{	
	params->id = 0;
	params->flags = (char *)malloc(sizeof(char) * 8);
	params->width = 0;
	params->precision = -1;
	params->length = 0;
	params->conversion = 0;
}

void	clear_params(t_params *params)
{
	params->id = 0;
	free(params->flags);
	params->width = 0;
	params->precision = 0;
	params->length = 0;
	params->conversion = 0;
}
