/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:15:42 by tpontine          #+#    #+#             */
/*   Updated: 2022/09/19 12:01:17 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct s_params
{
	char 	*flags;
	int		width;
	int		precision;
	char	*length;
	char	conversion;

} t_params; 

void	multiplyer(char **s, int multiplyer, int len);
float	to_pwr(int exp, int base);
int		ret_exp(float f);
void	adder(char **addto, char *num);
char	*initialize_sequence(int size, int addition);
char	*count_fraction(int exp);
char	*count_integer(int exp);
void	ft_ftoa(float f);

#endif
