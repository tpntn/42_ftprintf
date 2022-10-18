/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:46:24 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/19 02:23:37 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*apply_width(char **flo, t_params *params)
{
	size_t	len;
	int		width;
	char	*zeros;
	char	*ret;
	
	ft_putnbr(params->id);
	ft_putchar('\n');
	ft_putstr(params->flags);
	ft_putchar('\n');
	ft_putnbr(params->width);
	ft_putchar('\n');
	ft_putnbr(params->precision);
	ft_putchar('\n');
	ft_putnbr(params->length);
	ft_putchar('\n');
	ft_putchar(params->conversion);
	ft_putchar('\n');


	len = ft_strlen(*flo);
	width = params->width;
	if (width > (int)len)
	{
		ft_putstr("add somethign");
		zeros = ft_strnew((size_t)width - len);
		
		if (ft_strstr(params->flags,"0"))
			ft_memset(zeros, 32, (size_t)width - len - 1);
		else
			ft_memset(zeros, '0', (size_t)width - len - 1);
		ft_putstr(zeros);
	}
	
	ret = ft_strjoin(zeros, *flo);
	ft_strdel(flo);
	return (ret);	
}
