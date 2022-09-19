/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:15:42 by tpontine          #+#    #+#             */
/*   Updated: 2022/09/19 13:23:58 by tpontine         ###   ########.fr       */
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

#define STATE_NORMAL		0
#define STATE_FLAGS			1
#define STATE_WIDTH			2
#define STATE_PRECISION		3
#define	STATE_LENGTH		4
#define	STATE_CONVERSION	5

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
