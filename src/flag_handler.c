/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:46:24 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/19 23:21:17 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	append_string(char **s1, char *s2, int end)
{
	char	*s;
	
	s = ft_strdup(*s1);
	ft_strdel(s1);
	if (end)
		*s1 = ft_strjoin(s2, s);
	else
		*s1 = ft_strjoin(s, s2);
	ft_strdel(&s);	
}

int	apply_width(char **s, t_params *params)
{
	size_t	s_len;
	char	*pad;
	char	fill;
	char	end;

	s_len = ft_strlen(*s);
	if (params->width < s_len)
		return (0);
	pad = ft_strnew((size_t)params->width - s_len + 1);
	if (ft_strstr(params->flags, "0"))
		fill = '0';
	else
		fill = ' ';
	ft_memset(pad, fill, (size_t)params->width - s_len);
	end = 1;
	if (ft_strstr(params->flags, "-"))
		end = 0;
	append_string(s, pad, end);
	ft_strdel(&pad);
	return (0);
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
			append_string(s, "-", 1);
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
			append_string(s, "+", 1);
	}
}

void	apply_hash(char **s, int sign, t_params *params)
{
	if (params->conversion == 'f')
		if (ft_strstr(params->flags, "#") && params->precision == 0)
			append_string(s, ".", 0);
	if (params->conversion == 'o')
		if (ft_strstr(params->flags, "#"))
			append_string(s, "0",0);
	if (params->conversion == 'x')
		if (ft_strstr(params->flags, "#"))
			append_string(s, "0x",0);
	if (params->conversion == 'X')
		if (ft_strstr(params->flags, "#"))
			append_string(s, "0X",0);
}

// void	apply_minus(char **s, int sign, t_params *params)
// {
// 	int		i;
// 	size_t	pad_size;

// 	if (ft_strstr(params->flags, "-"))
// 	{
// 		pad_size = params->width - (int)ft_strlen(*s);
// 		if (pad_size > 0)
			
// 	}
// }

