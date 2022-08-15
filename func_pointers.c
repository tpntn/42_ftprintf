#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <libft.h>

// gcc func_pointers.c -I Libft/ -L libft -lft

// This creates a type "printer", which is a pointer to functions that return nothing and takes a void pointer.
typedef void (*printer)(va_list data);

struct tag
{
	char	id;
	printer func;
};

void ft_foo(va_list data)
{
	int a = va_arg(data, int);
	printf("%d", a);
}

// void	ft_print_float(void *data)
// {
// }

void ft_bar(void *data)
{
	int a = *(int *)data;
	printf("This is a function bar %d", a);
}

void ft_print_str(va_list data)
{
	char *str = va_arg(data, void*);
	printf("%s",str);
}

char	*initialize_sequence(int size, int addition) //size + add bytes
{

	int		i;
	char	*sequence;

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

void	adder(char **addto, char *num)
{
	int	i;
	int c;

	i = 0;
	c = 0;
	while (*(*addto + i) && *(num + c))
	{
		i++;
		c++;
	}
		
	while (*(*addto + i) != '.' || *(num + c) != '.')
	{
		if (*(*addto + i) + (*(num + c) - 48) > '9')
		{
			*(*addto + i - 1) += 1;
			*(*addto + i) += *(num + c) - 10 - 48;	
		}
		else
			*(*addto + i) += *(num + c) - 48;	
		i--;
		c--;
	}
}

void	multiplyer(char **s, int multiplyer)
{

}

char *count_fraction(int exp)
{
	char *seq;
	char *result;
	int	i;
	int c = 0;

	if (exp == 0)
	{
		printf("1.0");
		return ("1.0");
	}
		

	if (exp < 0)
		exp *= -1;

	i = exp + 1;

	seq = initialize_sequence(exp,2);
	seq[exp+1] = '1';
	
	char memo = 48;
	char digit;
	char next = 0;
	while (c < exp)
	{
		i = exp + 1;
		while (i >= 0)
		{
			digit = *(seq + i) - 48;
			digit *= 5;
			digit += next;
			next = 0;
			if (digit > 9)
			{
				next = digit / 10;
				digit %= 10;
				digit += 48;
				*(seq + i) = digit;
			}
			else
			{
				digit += 48;
				*(seq + i) = digit;
			}
			i--;
		}
		c++;
	}
	seq[1] = '.';
	printf("%s", seq);
	return (seq);
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

void	count_integer(int exp)
{
	int		i;
	char	*result;

	result = initialize_sequence(40,0);
	result[39] = '1';
	i = 0;
	
	while (i < exp)

}

void	ft_float_to_ascii(float f)
{
	int	*p;
	int	i;
	int	c;
	int sign;
	int	exp;
	char *manchar;
	char *result;
	
	exp = ret_exp(f);
	result = initialize_sequence(1000,0);

	p = (int *)&f;
	i = 22;
	c = 1;
	printf("hidden bit value:\t");
	count_fraction(exp);
	while (i >= 0)
	{
		printf("\nbit %d value:\t\t",i+1);
		if((*p >> i) & 1)
		{
			if (exp - c < 0)
				manchar = count_fraction(exp - c);
			else
				manchar = count_integer(exp - c);
			// adder(&result,manchar);
			// free(manchar);
		}
		c++;	
		i--;
	}
	i = 23;
	sign = 1;
	if (((*p >> 31) & 1))
		sign = -1;
}

// This is a function that takes a function and int as parameters.
// function pointer format: 
// 		<return value> (*<name>)(<params>)

/*
void ft_print(void (*f)(void), int i)
{
	printf("%d",i);
	f(); //This calls the function given as parameter.
}
*/

static struct tag flags[] = {
			{'d', ft_foo},
			{'s', ft_print_str}
	};

void	ft_printf(const char *str, ...)
{
	int		i;
	int		c;
	va_list	data;
	
	va_start(data, str);
	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == '%' )
		{
			c = 0;
			while (c < 10)
			{
				if (flags[c].id == *(str + i + 1))
				{
					flags[c].func(data);
					i++;
					break;
				}
				c++;
			}
		}
		else 
			putchar(*(str + i));
		i++;
	}
	va_end(data);
}


int main()
{
	float f = 0.1;
	// float f = 1.17549435082e-38;
	// float f = 0.15625;

	ft_float_to_ascii(f);
	// printf("%.126f\n",f);

	count_fraction(0);

	return (0);
}