#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

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



void	ft_float_to_ascii(float f)
{
	int	*p;
	int	i;
	
	union
     {
		float flo;
		struct
		{
			unsigned int	mantissa_all : 23; 
			unsigned int     exponent : 8;
			unsigned int     sign : 1;
		};
    } helper;

	helper.flo = f;
	p = (int *)&f;
	i = 32;
	while (i > 0)
	{
		printf("%d", (*p >> i) & 1);
		i--;
	}

	// printf("\n%d", helper.mantissa_hi);
	// printf("\n%d", helper.mantissa_lo);
	printf("\n%d", helper.sign);
	printf("\n%d", helper.exponent);
	printf("\n%d", helper.mantissa_all);
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
	int	i;
	int	c;
	va_list data;
	// int count;

	// count = 0;
	// i = 0;
	// while (*(str + i))
	// {
	// 	if (*(str + i) == '%')
	// 		count++;
	// 	i++;
	// }
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

	float f = -3.0/2.0;
	ft_printf("This is some number %d, print it", 123);
	printf("\n");
	ft_printf("This is some text %s, print it", "String");
	printf("\n");
	printf("Double: %.1f\n", 3.0/2.0);
	ft_itoa(8);
	printf("\n");
	ft_float_to_ascii(f);

	return (0);
}
