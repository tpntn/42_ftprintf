/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:15:42 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/16 09:30:40 by tpontine         ###   ########.fr       */
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
#include "Libft/libft.h"

#define STATE_NORMAL		0
#define STATE_FLAGS			1
#define STATE_WIDTH			2
#define STATE_PRECISION		3
#define	STATE_LENGTH		4
#define	STATE_CONVERSION	5

typedef struct s_params
{
	int		id;
	char 	*flags;
	int		width;
	int		precision;
	char	*length;
	char	conversion;

} t_params;

typedef struct s_plist
{
	t_params			params;
	struct s_plist		*next;
} t_plist;

typedef void (*func)(t_params *params, va_list data);

typedef struct s_type
{
	char	id;
	func	func;
} t_type;

void	multiplyer(char **s, int multiplyer, int len);
int		to_pwr(int exp, int base);
int		ret_exp(float f);
void	adder(char **addto, char *num);
char	*count_fraction(int exp);
char	*count_integer(int exp);
void	ft_ftoa(t_params *params, va_list data);

void	flags_handler(const char *c, int *state, t_params *params);
void	width_handler(const char *c, int *state, t_params *params);
void	precision_handler(const char *c, int *state, t_params *params, va_list data);
void	length_handler(const char *c, int *state, t_params *params, va_list data);
void	conv_handl(const char *c, int *state, t_params *params, va_list data);
void	normal_handler(const char *c, int *state);

void	initialize_params(t_params *params);
void	clear_params(t_params *params);
void	decimal_handler(int exp, char **result);



#endif
