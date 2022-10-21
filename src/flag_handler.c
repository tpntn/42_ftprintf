/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:46:24 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/21 10:04:41 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//LEAKS CHECK OK
void	append_string(char **s1, char *s2, int end)
{
	char	*temp;
	
	if (end)
		temp = ft_strjoin(s2, *s1);
	else
		temp = ft_strjoin(*s1, s2);
	free(*s1);
	*s1 = ft_strdup(temp);
	free(temp);
}

int	apply_width(char **s, t_params *params)
{
	size_t	s_len;
	char	*pad;
	char	fill;
	char	end;
	char	*temp;

	temp = ft_strdup(*s);
	// free(*s);
	s_len = ft_strlen(temp);
	if (params->width < (int)s_len)
		return (0);
	pad = ft_strnew((size_t)params->width - s_len + 1);
	fill = ' ';
	if (ft_strstr(params->flags, "0"))
		fill = '0';
	ft_memset(pad, fill, (size_t)params->width - s_len);
	end = 1;
	if (ft_strstr(params->flags, "-"))
		end = 0;
	append_string(&temp, pad, end);
	*s = ft_strdup(temp);
	ft_strdel(&pad);
	ft_strdel(&temp);
	return (0);
}

void	apply_sign(char **s, int sign, t_params *params)
{
	int		i;
	char	*temp;

	temp = ft_strdup(*s);
	free(*s);
	if (sign)
	{
		if (*temp == '0' && *(temp + 1) != '.')
			*(temp) = '-';
		else if (*temp == ' ')
		{
			i = 0;
			while (*(temp + i) == ' ')
				i++;
			*(temp + --i) = '-';
		}
		else
			append_string(&temp, "-", 1);
	}
	else if (ft_strstr(params->flags, "+"))
	{
		if (*temp == '0' && *(temp + 1) != '.')
			*(temp) = '+';
		else if (*temp == ' ')
		{
			i = 0;
			while (*(temp + i) == ' ')
				i++;
			*(temp + --i) = '+';
		}
		else
			append_string(&temp, "+", 1);
	}
	*s = ft_strdup(temp);
	free(temp);
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
	sign = 0;
}

// void	apply_minus(char **s, int sign, t_params *params)
// {
// 	int		i;
// 	size_t	pad_size;

// 	if (ft_strstr(params->flags, "-"))
// 	{
// 		pad_size = params->width - (int)ft_strlen(*s);
// 		if (pad_size > 0)
// 		{
			
// 			append_string(s,)
// 		}
			
// 	}
// }

