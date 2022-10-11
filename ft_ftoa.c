/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:02:54 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/11 11:13:27 by tpontine         ###   ########.fr       */
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

// char	*initialize_sequence(int size, int addition) //size + add bytes
// {
// 	int		i;
// 	char	*sequence;

// 	if (size < 0)
// 		size *= -1;
// 	if (addition < 0)
// 		addition *= -1;
// 	size += addition;
// 	sequence = (char *)malloc(sizeof(char) * (size));
// 	if (sequence)
// 	{
// 		ft_memset(sequence, 0, size);	
// 		i = 0;
// 		while (i < size - 1)
// 			sequence[i++] = '0';
// 		return (sequence);
// 	}
// 	return (0);
// }

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
/*
void	ft_ftoa(float f)
{
	int	*p;
	int	i;
	int	c;
	int	exp;
	char *manchar;
	char *result_frac;
	// char *result_int;
	int	result_int;
	
	exp = ret_exp(f);
	result_frac = malloc_and_setzero(200);
	// result_int = malloc_and_setzero(40);
	result_frac[1] = '.';

	p = (int *)&f;
	i = 0;
	c = 23;
	result_int = 1;
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
				// ft_strdel(&manchar);
			}
			else
			{
				result_int += to_pwr(2,i);
				// printf("counting with:%d\n",exp-c);
				// manchar = count_integer(exp - c);
				// adder(&result_int,manchar);
				// printf("adding bit%d:\t%s\n", i+1, manchar);
				// printf("result:\t\t%s\n", result_int);
				// ft_strdel(&manchar);
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
*/
int	main()
{
	//TESTAA TÄMÄ KOULULLA, ETTÄ TULEE OIKEA LOPPUTULOS
	char	*fraction;
	char	*total = malloc_and_setzero(151);
	int	result_int = 1;
	total[1] = '.';

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

	for (int i = 0; i <= 3; i++)
	{
		result_int += to_pwr(2,i);
		printf("%d\n", result_int);
	}

	

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