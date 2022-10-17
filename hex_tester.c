#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * 0 - 9
 *
 * a = 10
 * b = 11
 * c = 12
 * d = 13
 * e = 14
 * f = 15
 *
 * 
 * 01 = 1
 * 1f = 15 + 16 = 31 (base is 16) 
 * 20a = (16^0 x 10) + (16^1 x 0) + (16^2 x 2) = 522
 *
 *  2^3 = 2x2x2
 */

int	ft_exp(int base, int exp)
{
	int i = 0;
	int result = 1;
	while (i < exp)
	{
		result *= base;
		i++;
	}
	return (result);
}

int	hex_to_int(int a)
{
	int i = 0;
	int result = 0;
	int exp = 0;
	while (i < (sizeof(a) * 8))
	{
		printf("%d", (a >> i & 1));
		result += (a >> i & 1) * ft_exp(2,exp);
		i++;
		exp++;
	}
	printf("\n\n%d\n", result);
	return (0);
}

char	set_hex(int a)
{
	if (a < 9)
		return (a + 48);
	return (a + 55);
}

char	*newstr(int size)
{
	char	*output;

	output = (char *)malloc(sizeof(char) * size);
	memset(output, 0, sizeof(char) * size);
	return (output);
}

char	*int_to_hex(int a)
{
	static char	*output;
	static int	pos = 0;
	static int	exp = 0;

	if (!output)
	{
		output = newstr(9);
		if (a < 0)
		{
			a *= -1;	
			*output = '-';
			pos++;
		}
		while ((a / ft_exp(16,exp) > 16))
			exp++;
	}
	if (a < 16 && exp == 0)
	{
		*(output + pos) = set_hex(a);
		return (output);
	}
	else
	{
		*(output + pos++) = set_hex(a / ft_exp(16, exp));		
		return (int_to_hex(a % ft_exp(16, (exp--))));
	}
}

int	main(int argc, char **argv)
{
	
	if (argc != 2)
	{
		printf("give me a number\n");
		return(0);	
	}
	int b = atoi(argv[1]);
	printf("%s\n",int_to_hex(b));
	return (0);
}
