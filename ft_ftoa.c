/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:02:54 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/14 10:44:01 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


// #define FLT_MAX 3.402823466e+38F /* max value */
// #define FLT_MIN 1.175494351e-38F /* min positive value */

/*
3.4e2 = 340
1.17e-2 = 0.0117
3.40282346600000000000000000000000000000
*/


void	multiplyer(char **s, int multiplyer, int len)
{
	int		i;
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

int	to_pwr(int exp, int base)
{
	int ret;
	int	i;
	ret = base;
	if (exp == 0)
		return (1);
	i = exp - 1;
	while (i--)
		ret *= base;
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
	while (*(num + i))
		i++;
	i--;
	while (*(num + i) != '.')
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

// mallocs size + 1, set all values to '0' char and terminating NULL char
char	*malloc_and_setzero(int size)
{
	char	*s;
	s = (char *)malloc(sizeof(char) * size + 1);
	if (!s)
		return (0);
	*(s + size) = 0;
	size--;
	while(size)
		*(s+size--) = '0';
	*s = '0';
	return (s);
}

//counts and returns the value of fraction based exponent given
char *count_fraction(int exp)
{
	char *result;
	int c;

	if (exp == 0)
		return ("1.0");
	
	if (exp < 0)
		exp *= -1;
	result = malloc_and_setzero(exp + 2);
	result[exp+1] = '1';
	c = 0;
	while (c < exp)
	{
		multiplyer(&result, 5, exp + 2);
		c++;
	}
	result[1] = '.';
	return (result);
}

//count the integer based on exp
char	*count_integer(int exp)
{
	int		i;
	char	*result;

	result = malloc_and_setzero(40);
	result[39] = '1';

	i = 0;
	while (i < exp)
	{
		multiplyer(&result,2,40);
		i++;
	}
	return (result);
}

char	*handle_fraction(int exp, char **result_frac)
{
	size_t	len_f;
	size_t	len_m;
	char	*temp;
	char	*new;
	char	*m;
	char	*addition;
	
	temp = ft_strdup(*result_frac);
	ft_strdel(result_frac);
	m = count_fraction(exp);
	len_f = ft_strlen(temp);
	len_m = ft_strlen(m);
	new = (char*)malloc(sizeof(char) * (len_m + 2));
	addition = (char*)malloc(sizeof(char) * (len_m - len_f + 1));
	ft_memset(addition, '0', (size_t)(len_m - len_f));
	new = ft_strcat(temp, addition);
	exp = 0;
	adder(&new, m);
	ft_strdel(&m);
	ft_strdel(&temp);
	return (new);
}

void	handle_integer(int exp, char **result_int)
{
	char	*m;
	
	m = count_integer(exp);
	adder(result_int, m);
	ft_strdel(&m);
}

void	ft_ftoa(float f, int precision)
{
	int	*p;
	int	i;
	int	c;
	int	exp;
	char *result_frac;
	char *result_int;
	
	exp = ret_exp(f);
	result_frac = (char *)malloc(sizeof(char) * 4);
	result_frac = ft_strcpy(result_frac, "0.0");
	result_frac[3] = '\0';
	result_int = malloc_and_setzero(40);

	p = (int *)&f;
	i = 22;
	if (exp < 0 && exp != -126)
		handle_fraction(exp, &result_frac);
	else
		handle_integer(exp, &result_int);
	exp--;
	while (i >= 0)
	{
		if((*p >> i) & 1)
		{
			if (exp < 0)
				handle_fraction(exp, &result_frac);
			else
				handle_integer(exp, &result_int);
		}	
		exp--;	
		i--;
	}
	if (((*p >> 31) & 1))
		ft_putchar('-');
	int a = 0;
	while (*(result_int + a) == '0' && a < 39)
		a++;
	while (*(result_int + a))
		ft_putchar(*(result_int + a++));
	i = 0;
	c = 1;
	while (c < (int)ft_strlen(result_frac) && c <= precision + 1)
		ft_putchar(*(result_frac + c++));
	
}

int	main()
{	
	// float f = 123.23;
	// float f = 0.1;
	float f = 0.1123123123;
	// float f = -0.1123123123;
	// float f = __FLT_MIN__; //This does not work
	// float f = __FLT_MAX__;
	
	printf("%.17f\n",f);
	ft_ftoa(f,17);
	
	return (0);
}
