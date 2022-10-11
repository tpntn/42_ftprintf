/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:02:54 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/11 21:40:57 by tpontine         ###   ########.fr       */
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

char *count_fraction(int exp)
{
	char *result;
	int	i;
	int c;

	if (exp == 0)
		return ("1.0");
	if (exp < 0)
		exp *= -1;
	i = exp + 1;
	result = malloc_and_setzero(exp + 2);
	result[exp+1] = '1';
	c = 0;
	while (c < exp)
	{
		multiplyer(&result, 5, exp+2);
		c++;
	}
	result[1] = '.';
	return (result);
}


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

void	ft_ftoa(float f, int precision)
{
	int	*p;
	int	i;
	int	c;
	int	exp;
	char *manchar;
	char *result_frac;
	char *result_int;
	
	exp = ret_exp(f);
	result_frac = malloc_and_setzero(200);
	result_frac[1] = '.';
	result_int = malloc_and_setzero(40);

	p = (int *)&f;
	i = 22;
	// printf("exponent: %d\n", exp);
	if (exp != -126) //this counts the hidden bit
	{
		if (exp < 0)
		{
			// printf("counting the hidden bit:%d\n", exp);
			manchar = count_fraction(exp);
			adder(&result_frac,manchar);
			// printf("adding bit%d:\t%s\n", i+1, manchar);
			// printf("result:\t\t%s\n", result_frac);
			// ft_bzero(manchar, ft_strlen(manchar));
			ft_strdel(&manchar);
		}
		else
		{
			manchar = count_integer(exp);
			adder(&result_int, manchar);
			// printf("counting with:%d\n",exp);
			// printf("adding bit%d:\t%s\n", i+1, manchar);
			// printf("result:\t\t%s\n", result_int);
			// ft_bzero(manchar, ft_strlen(manchar));
			ft_strdel(&manchar);
		}
		exp--;
	}
	c = exp;
	while (i >= 0)
	{
		if((*p >> i) & 1)
		{
			if (c < 0)
			{
				// printf("counting with:%d\n", c);
				manchar = count_fraction(c);
				adder(&result_frac,manchar);
				// printf("adding bit%d:\t%s\n", i+1, manchar);
				// printf("result:\t\t%s\n", result_frac);
				// ft_bzero(manchar, ft_strlen(manchar));
				ft_strdel(&manchar);
			}
			else
			{
				// printf("counting with:%d\n",c);
				manchar = count_integer(c);
				adder(&result_int, manchar);
				// printf("adding bit%d:\t%s\n", i+1, manchar);
				// printf("result:\t\t%s\n", result_int);
				// ft_bzero(manchar, ft_strlen(manchar));
				ft_strdel(&manchar);
			}
		}	
		c--;	
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
	// while (*(result_frac + i))
	// 	i++;
	while (c < ft_strlen(result_frac) && c <= precision)
		ft_putchar(*(result_frac + c++));
	
}

int	main()
{
	//TESTAA TÄMÄ KOULULLA, ETTÄ TULEE OIKEA LOPPUTULOS
	char	*fraction;
	char	*total = malloc_and_setzero(151);
	int	result_int = 0;
	total[1] = '.';
	
	// float f = 123.23;
	// float f = 0.1;
	// float f = 0.1123123123;
	float f = -0.1123123123;
	// float f = __FLT_MIN__; //This does not work
	// float f = __FLT_MAX__;

	// for (int i = 0; i <= 149; i++)
	// {
	// 	fraction = count_fraction(i);
	// 	// printf("exp -%d: %s\n",i,fraction);
	// }

	// char *first = count_fraction(-17);
	// char *sec = count_fraction(-18);

	// printf("%s\n", first);
	// printf("%s\n", sec);

	// printf("%s\n", total);
	// adder(&total, first);
	// printf("%s\n", total);
	// adder(&total, sec);
	// printf("%s\n", total);

	// for (int i = 8; i >= 5; i--)
	// {
	// 	printf("exp: %d result: %d\n",i,to_pwr(i,2));
	// 	result_int += to_pwr(i,2);
	// 	printf("%d\n", result_int);
	// }

	// printf("%d", to_pwr(8,2));

	ft_ftoa(f,12);

	return (0);
}

// exp -14 -15
//0.000091552734375
//0.000091552734375

// exp -17 -18
//0.000011444091796875
//0.000011444091796875

// STATUS
//count fraction tulostaa nyt oikean aina "loppuun saakka eli -126"