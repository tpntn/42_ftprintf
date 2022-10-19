/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:46:24 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/19 11:50:53 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	apply_width(char **s, t_params *params)
{
	size_t	len;
	int		width;
	char	*zeros;
	char	*ret;

	len = ft_strlen(*s);
	width = params->width;
	if (width > (int)len)
	{
		zeros = ft_strnew((size_t)width - len + 1);
	if (!ft_strstr(params->flags,"0"))
		ft_memset(zeros, ' ', (size_t)width - len);
	else
		ft_memset(zeros, '0', (size_t)width - len);
	}
	if (!ft_strstr(params->flags, "-"))
		ret = ft_strjoin(zeros, *s);
	else
		ret = ft_strjoin(*s, ret);
	ft_strdel(s);
	ft_strdel(&zeros);
	*s = ft_strdup(ret);
	ft_strdel(&ret);
}

static void set_sign(char **s, int sign, t_params *params, int i)
{
	if (sign)
		*(*s + i) = '-';
	if (ft_strstr(params->flags, "+") && !sign)
		*(*s + i) = '+';
}

void	apply_sign(char **s, int sign, t_params *params)
{
	int		i;
	char	*temp;

	i = 0;
	if (*(*s + 0) == '0')
		set_sign(s, sign, params, 0);
	else if (*(*s + 0) == ' ')
	{
		while (*(*s + i) == ' ')
			i++;
		i--;
		set_sign(s, sign, params, i);
	}
	else
	{
		temp = ft_strdup(*s);
		ft_strdel(s);
		if (sign)
			*s = ft_strjoin("-", temp);
		if (ft_strstr(params->flags, "+") && !sign)
			*s = ft_strjoin("+", temp);
		ft_strdel(&temp);
	}
	
}

