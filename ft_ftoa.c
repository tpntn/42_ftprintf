/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:02:54 by tpontine          #+#    #+#             */
/*   Updated: 2022/09/19 11:16:43 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	multiplyer(char **s, int multiplyer, int len)
{
	int		i;
	char	memo = 48;
	char	digit;
	char	next = 0;

	i = len - 1;
	while (i >= 0)
	{
		digit = *(*s + i) - 48;
		digit *= multiplyer;
		digit += next;
		next = 0;
		if (digit > 9)
		{
			next = digit / 10;
			digit %= 10;
			digit += 48;
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

float	to_pwr(int exp, int base)
{
	float	ret;
	int		i;
	int		neg;
	
	ret = 1.0;
	i = 0;
	neg = 0;
	if (exp == 0)
		return (1.0);
	if (exp < 0)
	{
		exp *= -1;
		neg = 1;
	}
	while (i++ < exp)
		ret *= (float)base; 

	if (neg)
		return (1 / ret);
	return (ret);
}

int		ret_exp(float f)
{
	int	exp;
	int	e;
	int i;
	int	*p;

	p = (int *)&f;
	i = 23;
	exp = 0;
	e = 0;
	while (i < 31)
		exp += ((*p >> i++) & 1) * to_pwr(e++,2);
	
	exp += -127;

	return (exp);
}

void	adder(char **addto, char *num)
{
	int	i;

	i = 0;
	while (*(num + i) && *((*addto + i)))
		i++;
	i--;

	// while (*(*addto + i) != '.' && *(num + i) != '.')
	while (i > 1)
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

char	*initialize_sequence(int size, int addition) //size + add bytes
{
	int		i;
	char	*sequence;

	if (size < 0)
		size *= -1;
	if (addition < 0)
		addition *= -1;
	size += addition;
	sequence = (char *)malloc(sizeof(char) * (size));
	if (sequence)
	{
		ft_memset(sequence, 0, size);	
		i = 0;
		while (i < size - 1)
			sequence[i++] = '0';
		return (sequence);
	}
	return (0);
}

char *count_fraction(int exp)
{
	char *seq;
	char *result;
	int	i;
	int c = 0;

	if (exp == 0)
	{
		// printf("1.0");
		return ("1.0");
	}
		
	if (exp < 0)
		exp *= -1;

	i = exp + 1;

	seq = initialize_sequence(exp,2);
	seq[exp+1] = '1';
	while (c < exp)
	{
		multiplyer(&seq, 5, exp+2);
		c++;
	}
	seq[1] = '.';
	// printf("%s\n", seq);
	return (seq);
}

char	*count_integer(int exp)
{
	int		i;
	char	*result;

	result = initialize_sequence(40,0);
	result[39] = '1';

	i = 0;
	while (i < exp)
	{
		multiplyer(&result,2,40);
		i++;
	}
	return (result);
}

void	ft_ftoa(float f)
{
	int	*p;
	int	i;
	int	c;
	int	exp;
	char *manchar;
	char *result_frac;
	char *result_int;
	
	exp = ret_exp(f);
	result_frac = initialize_sequence(exp - 23,3);
	result_int = initialize_sequence(40,1);
	result_frac[1] = '.';

	p = (int *)&f;
	i = 0;
	c = 23;
	
	while (i < 23)
	{
		if((*p >> i) & 1)
		{
			if (exp - c < 0)
			{
				// printf("counting with:%d\n",exp-c);
				manchar = count_fraction(exp - c);
				adder(&result_frac,manchar);
				// printf("adding bit%d:\t%s\n", i+1, manchar);
				// printf("result:\t\t%s\n", result_frac);
			}
			else
			{
				// printf("counting with:%d\n",exp-c);
				manchar = count_integer(exp - c);
				adder(&result_int,manchar);
				// printf("adding bit%d:\t%s\n", i+1, manchar);
				// printf("result:\t\t%s\n", result_int);
			}
			ft_bzero(manchar, ft_strlen(manchar));
			ft_strdel(&manchar);
		}	
		c--;	
		i++;
	}
	// printf("%d\n",exp);
	if (exp != -126)
	{
		// printf("counting hidden bit:");
		if (exp < 0)
		{	
			manchar = count_fraction(exp);
			adder(&result_frac,manchar);
			// printf("adding bit:\t%s\n", manchar);
			// printf("result:\t\t%s\n", result_frac);
		}
		else
		{
			manchar = count_integer(exp);
			adder(&result_int,manchar);
			// printf("adding bit:\t%s\n", manchar);
			// printf("result:\t\t%s\n", result_int);
		}
			
	}
	
	if (((*p >> 31) & 1))
		ft_putchar('-');

	i = 0;
	while (result_int[i] == '0')
		i++;
	if (i != 40)
		ft_putstr(result_int + i);
	else
		ft_putchar('0');
	i = 0;
	c = 1;
	while (*(result_frac + i))
		i++;
	while (c < i)
		ft_putchar(*(result_frac + c++));
	
}