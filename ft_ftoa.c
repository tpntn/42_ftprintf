/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:02:54 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/14 08:36:33 by tpontine         ###   ########.fr       */
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

// [0][.][0][\0]
/*
result_frac = "0.25";
len_frac = 4;
m = "0.125";
new = [][][][][][];
new = [0][.][2][5][0][\0];
new = [0][.][3][7][5][\0];
*/

char	*handle_fraction(int exp, char *result_frac)
{
	size_t	len_f;
	size_t	len_m;
	char	*new;
	char	*m;
	char	*addition;
	
	m = count_fraction(exp);
	len_f = ft_strlen(result_frac);
	len_m = ft_strlen(m);
	new = (char*)malloc(sizeof(char) * (len_m + 2));
	addition = (char*)malloc(sizeof(char) * (len_m - len_f + 1));
	ft_memset(addition, '0', (size_t)(len_m - len_f));
	new = ft_strcat(result_frac, addition);
	exp = 0;
	adder(&new, m);
	printf("output value: %s\n", new);
	ft_strdel(&m);
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
	result_frac[0] = '0';
	result_frac[1] = '.';
	result_frac[2] = '0';
	result_frac[3] = '\0';
	result_int = malloc_and_setzero(40);

	p = (int *)&f;
	i = 22;
	printf("exponent: %d\n", exp);
	printf("result_frac: %s\n",result_frac);
	if (exp < 0 && exp != -126)
		handle_fraction(exp, result_frac);
	else
		handle_integer(exp, &result_int);
	exp--;
	printf("result_frac: %s\n",result_frac);
	while (i >= 0)
	{
		if((*p >> i) & 1)
		{
			if (exp < 0)
			{
				printf("exponent: %d\n", exp);
				handle_fraction(exp, result_frac);
				printf("result:\t\t%s\n", result_frac);
			}
			else
			{
				printf("exponent: %d\n", exp);
				handle_integer(exp, &result_int);
				printf("result:\t\t%s\n", result_int);
			}
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
	// while (*(result_frac + i))
	// 	i++;
	while (c < (int)ft_strlen(result_frac) && c <= precision)
		ft_putchar(*(result_frac + c++));
	
}

int	main()
{
	//TESTAA TÄMÄ KOULULLA, ETTÄ TULEE OIKEA LOPPUTULOS
	// char	*fraction;
	// char	*total = malloc_and_setzero(151);
	// int	result_int = 0;
	// total[1] = '.';
	
	// float f = 123.23;
	// float f = 0.1;
	// float f = 0.1123123123;
	// float f = -0.1123123123;
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

	// ft_ftoa(f,12);

	char *result_frac;
	// char *m;
	
	result_frac = (char *)malloc(sizeof(char) * 4);
	result_frac[0] = '0';
	result_frac[1] = '.';
	result_frac[2] = '0';
	result_frac[3] = '\0';

	// for (int i = 0; i > -12; i--)
	// {
	// 	// result_frac = handle_fraction(i, result_frac);
	// 	m = count_fraction(i);
	// 	printf("result: %s\n", m);
	// }
	
	// printf("result: %s\n", s);
	// printf("manchar:%s\n", m);
	// adder(&s,m);
	// printf("result: %s\n", s);

	printf("fraction in the start: %s\n", result_frac);
	result_frac = handle_fraction(-4, result_frac);
	result_frac = handle_fraction(-5, result_frac);
	result_frac = handle_fraction(-8, result_frac);
	result_frac = handle_fraction(-9, result_frac);
	result_frac = handle_fraction(-12, result_frac);
	result_frac = handle_fraction(-13, result_frac);
	result_frac = handle_fraction(-16, result_frac);
	result_frac = handle_fraction(-17, result_frac);
	result_frac = handle_fraction(-20, result_frac);
	result_frac = handle_fraction(-21, result_frac);
	result_frac = handle_fraction(-24, result_frac);
	result_frac = handle_fraction(-25, result_frac);
	result_frac = handle_fraction(-27, result_frac);
	
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