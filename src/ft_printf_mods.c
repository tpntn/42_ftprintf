/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_mods.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:10:12 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/19 16:20:28 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_type_specifier(char str)
{
	const char	*types = "csdioxXuFfeEaAgGnp";

	while (*types)
	{
		if (*types == str)
			return (1);
		types++;
	}
	return (0);
}

int	is_flag(char c)
{
	const char	flags[] = "-+ #0";
	int			i;

	i = 0;
	while (flags[i])
	{
		if (flags[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_length_mod(char c)
{
	const char	flags[] = "hlqLjzZt";
	int			i;

	i = 0;
	while (flags[i])
	{
		if (flags[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_conv_mod(char c)
{
	const char	flags[] = "diouxXeEfFgGaAcsCSpnm%";
	int			i;

	i = 0;
	while (flags[i])
	{
		if (flags[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	check_params(t_params **params)
{
	if ((*params)->precision == -1)
		(*params)->precision = 6;
}
