#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <libft.h>

// This creates a type "printer", which is a pointer to functions that return nothing and takes a void pointer.
typedef void (*printer)(va_list data);

struct tag
{
	char	id;
	printer func;
};

// This is a function that takes nothing and return nothing.
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

	i = 20;
	while (i >= 0)
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

void count_bit_value(int exp)
{
	char *seq;
	int	i;
	int c = 0;

	if (exp < 0)
		exp *= -1;

	i = exp + 1;

	seq = initialize_sequence(exp,2);
	seq[exp+1] = '1';
	
	char memo = 48;
	char digit;
	char next = 0;
	// printf("%s\n", seq);
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
	// return (seq);
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

void	ft_float_to_ascii(float f)
{
	int	*p;
	int	i;
	int	c;
	int sign;
	int	exp;
	int addition;
	char *manchar;
	char *sequence;
	

	exp = ret_exp(f);
	printf("exp: %d\n", exp);
	manchar = initialize_sequence(exp, 3); //[1][.][1][\0]
	sequence = initialize_sequence(exp,3);



	p = (int *)&f;
	i = 22;
	c = 1;
	sequence[0] = '1';
	printf("bit 23 value: ");
	count_bit_value(exp);
	while (i >= 0)
	{
		printf("\nbit %d value: ",i);
		if((*p >> i) & 1) //jos bitti on 1, tee jotain.. eli laske
		{
			count_bit_value(exp - c); //save this value to some char* and then use adder...
		}
		c++;	
		i--;
	}
	i = 23;
	sign = 1;
	if (((*p >> 31) & 1))
		sign = -1;

	// i = 1;
	// while (i < 23)
	// {
	// 	if (sequence[i] == '1')
	// 	{
	// 		printf("adding:%s\n", bit[i]);
	// 		adder(&manchar, bit[i]);
	// 	}
	// 	i++;
	// }
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
	float f = 0.2421875;

	ft_float_to_ascii(f);
	// printf("%.126f\n",f);

	return (0);
}