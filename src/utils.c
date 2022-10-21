/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:40:34 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/20 21:09:48 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	safe_add_one(char *digit, char *next)
{
	*next = *digit / 10;
	*digit %= 10;
	*digit += 48;
}

void	multiplyer(char **s, int multiplyer, int len)
{
	int		i;
	char	digit;
	char	next;

	next = 0;
	i = len - 1;
	while (i >= 0)
	{
		digit = *(*s + i) - 48;
		digit *= multiplyer;
		digit += next;
		next = 0;
		if (digit > 9)
		{
			safe_add_one(&digit, &next);
			*(*s + i) = digit;
		}
		else
		{
			digit += 48;
			*(*s + i) = digit;
		}
		i--;
	}
}

int	to_pwr(int exp, int base)
{
	int	ret;
	int	i;

	ret = base;
	if (exp == 0)
		return (1);
	i = exp - 1;
	while (i--)
		ret *= base;
	return (ret);
}

void	adder(char **addto, char *num)
{
	int	i;

	i = 0;
	while (*(num + i))
		i++;
	i--;
	while (*(num + i) != '.' && i)
	{
		if (*(*addto + i) + (*(num + i) - 48) > '9')
		{
			*(*addto + i - 1) += 1;
			*(*addto + i) += *(num + i) - 10 - 48;
		}
		else
			*(*addto + i) += *(num + i) - 48;
		i--;
	}
}

int	ret_exp(float f)
{
	int	exp;
	int	e;
	int	i;
	int	*p;

	p = (int *)&f;
	i = 23;
	exp = 0;
	e = 0;
	while (i < 31)
		exp += ((*p >> i++) & 1) * to_pwr(e++, 2);
	exp += -127;
	return (exp);
}
