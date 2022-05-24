#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

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

void	ft_putchar(char c)
{
	write(1,&c,1);
}

void	ft_itoa(int a)
{
	ft_putchar(a + 48);
}

float	to_pwr(int exp)
{
	float ret;
	int i;
	int	neg;
	
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
	while (i < exp)
	{
		ret *= 2.0; 
		i++;
	}
	if (neg)
		return (1 / ret);
	return (ret);
}

void	ft_float_to_ascii(float f)
{
	int	*p;
	int	i;
	float newf;
	int	exp;

	p = (int *)&f;
	i = 0;
	while (i < 32)
	{
		printf("%d", (*p >> i) & 1);
		i++;
	}
	
	newf = 0;
	int e = -23;
	i = 0;
	while (i < 23)
	{
		newf += ((*p >> i++) & 1) * to_pwr(e++);
		printf("bit: %d, e: %d, newf: %f\n",((*p >> (i - 1)) & 1), (e-1), newf); //remove this and curly braces
	}
	newf += 1.0;
	printf("\nmantissa has value %f\n", newf);

	exp = 0;
	e = 0;
	while (i < 31)
	{
		exp += ((*p >> i++) & 1) * to_pwr(e++);
		printf("bit: %d, e: %d, exp: %d\n",((*p >> (i-1)) & 1), (e-1), exp); //remove this and curly braces
	}
	exp += -127;
	printf("exponent has value of: %d\n", exp);

	float sign;
	sign = 1;
	if (((*p >> 31) & 1))
		sign = -1;
	printf("Final result: %f", sign * (float)to_pwr(exp) * newf);
}

// This is a function that takes a function and and int as parameters.
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
	// array to contain required tags
	
	// int data1 = 123;
	// char *data3 = "what ever";
	// Here we call ft_print and give it a function as parameter.

	// float f = -3.0/2.0;
	float f = 0.760025024414;
	ft_printf("This is some number %d, print it", 123);
	printf("\n");
	ft_printf("This is some text %s, print it", "String");
	printf("\n");
	printf("Double: %.1f\n", -3.0/2.0);
	ft_itoa(8);
	printf("\n");
	// ft_float_to_ascii(f);
	printf("max float: %f\n", __FLT_MAX__);
	printf("min float: %f\n", __FLT_MIN__);

	ft_float_to_ascii(f);

	return (0);
}
