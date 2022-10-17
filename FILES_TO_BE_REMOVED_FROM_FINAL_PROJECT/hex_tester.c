#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

int	hex_to_int(unsigned long a)
{
	unsigned long i = 0;
	int result = 0;
	int exp = 0;
	while (i < (sizeof(a) * 8))
	{
		// printf("%d", (a >> i & 1));
		result += (a >> i & 1) * ft_exp(2,exp);
		i++;
		exp++;
	}
	printf("\n\n%d\n", result);
	return (0);
}

char	set_hex(int a)
{
	if (a <= 9)
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

char	*int_to_hex(long long a)
{
	char				*output;
	long long			pos = 0;
	long long			exp = 0;

	output = NULL;
	if (!output)
	{
		output = newstr(50);
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

int	main()
{
	int int_max = INT_MAX;
	int int_min = INT_MIN;
	printf("INT_MAX printf: %x\n", int_max);
	printf("INT_MIN printf: %x\n", int_min);
	printf("%s\n",int_to_hex(int_min));
	return (0);
}