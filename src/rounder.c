/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rounder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:49:44 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/20 15:11:16 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	rounder(char **fraction, int precision, int memo)
{
	if ((precision > (int)ft_strlen(*fraction) - 2))
		return (0);
	if ((*fraction)[precision + 2] < '5' && !memo)
		return (0);
	if (memo)
	{
		if ((*fraction)[precision + 1] + 1 > '9')
		{
			(*fraction)[precision + 1] = '0';
			return (rounder(fraction, precision - 1, 1));
		}
		else
			(*fraction)[precision + 1]++;
	}
	if ((*fraction)[precision + 2] >= '5' && !memo)
	{
		if ((*fraction)[precision + 1] + 1 > '9')
		{
			(*fraction)[precision + 1] = '0';
			return (rounder(fraction, precision - 1, 1));
		}
		else
			(*fraction)[precision + 1]++;
	}
	return (0);
}
