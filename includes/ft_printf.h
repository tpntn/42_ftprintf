/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:15:42 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/19 16:46:52 by tpontine         ###   ########.fr       */
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
#include "libft.h"

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
	int		length;
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

int		ft_printf(const char *str, ...);
void	multiplyer(char **s, int multiplyer, int len);
int		to_pwr(int exp, int base);
int		ret_exp(float f);
void	adder(char **addto, char *num);
char	*count_fraction(int exp);
char	*count_integer(int exp);
void	ft_ftoa(t_params *params, va_list data);
char	*malloc_and_setzero(int size);
char	*handle_fraction(int exp, char *result_frac);
void	handle_integer(int exp, char *result_int);
int		rounder(char **fraction, int precision, int memo);

void	flags_handler(const char *c, int *state, t_params *params, va_list data);
void	width_handler(const char *c, int *state, t_params *params, va_list data);
void	prec_handler(const char *c, int *state, t_params *params, va_list data);
void	len_handler(const char *c, int *state, t_params *params, va_list data);
void	conv_handl(const char *c, int *state, t_params *params, va_list data);
void	normal_handler(const char *c, int *state);
void	check_params(t_params **params);
int		is_conv_mod(char c);
int		is_length_mod(char c);
int		is_flag(char c);
void	apply_width(char **s, t_params *params);
void	apply_sign(char **s, int sign, t_params *params);
void	apply_hash(char **s, int sign, t_params *params);


void	initialize_params(t_params *params);
void	clear_params(t_params *params);
void	decimal_handler(int exp, char **result);

void	ft_printf_itoa(t_params *params, va_list data);

void	ft_puts(t_params *params, va_list data);
void	ft_putc(t_params *params, va_list data);
void	ft_ptr(t_params *params, va_list data);

void	__ft_itoa_unsigned(t_params *params, va_list data);
int		__ft_itoa(t_params *params, va_list data);

int	set_radix(t_params *params);
long long	set_number(t_params *params, va_list data);



#endif
