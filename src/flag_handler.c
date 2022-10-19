/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:46:24 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/19 16:44:54 by tpontine         ###   ########.fr       */
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
		if (!ft_strstr(params->flags, "-"))
			ret = ft_strjoin(zeros, *s);
		else
			ret = ft_strjoin(*s, ret);
		ft_strdel(s);
		ft_strdel(&zeros);
		*s = ft_strdup(ret);
		ft_strdel(&ret);
	}
}

void	append_string(char **s1, char *s2)
{
	char	*temp;

	temp = ft_strdup(*s1);
	ft_strdel(s1);
	*s1 = ft_strjoin(s2, temp);
	ft_strdel(&temp);
}

void	apply_sign(char **s, int sign, t_params *params)
{
	int		i;
	
	if (sign)
	{
		if (*(*s) == '0')
			*(*s) = '-';
		else if (*(*s) == ' ')
		{
			i = 0;
			while (*(*s + i) == ' ')
				i++;
			*(*s + --i) = '-';
		}
		else
			append_string(s, "-");
	}
	else if (ft_strstr(params->flags, "+"))
	{
		if (*(*s) == '0')
			*(*s) = '+';
		else if (*(*s) == ' ')
		{
			i = 0;
			while (*(*s + i) == ' ')
				i++;
			*(*s + --i) = '+';
		}
		else
			append_string(s, "+");
	}
}

void	apply_hash(char **s, int sign, t_params *params)
{
	if (ft_strstr(params->flags, "#") && params->precision == 0)
		append_string(s, ".");
}

void	apply_minus(char **s, int sign, t_params *params)
{
	int		i;
	char	*temp;

	if (ft_strstr(params->flags, "-"))
	{
		i = 0;
		while (*(*s + i) == '0' || *(*s + i) == ' ')
			i++;
		temp = ft_strdup(*s);
		ft_strdel(s);
		s* = ft_strdup(temp + i);
		ft_strdel(&temp);
	}
}

