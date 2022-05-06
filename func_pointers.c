#include <stdio.h>
#include <string.h>

// This creates a type "printer", which is a pointer to functions that return nothing and takes avoid pointer.
typedef void (*printer)(void *value);

struct tag
{
	char	id;
	printer func;
};

// This is a function that takes nothing and return nothing.
void ft_foo(void *data)
{
	int a = *(int *)data;
	printf("%d", a);
}

void ft_bar(void *data)
{
	int a = *(int *)data;
	printf("This is a function bar %d", a);
}

void ft_print_str(void *data)
{
	char *str = strdup(data);
	printf("%s",str);
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

void	ft_printf(char *str, struct tag *array, void *data)
{
	int	i;
	int	c;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == '%' )
		{
			c = 0;
			while (c < 10)
			{
				if (array[c].id == *(str + i + 1))
				{
					array[c].func(data);
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
	}

int main()
{
	// array to contain required tags
	struct tag flags[] = {
			{'d', ft_foo},
			{'s', ft_print_str}
	};
	int data1 = 123;
	char *data3 = "what ever";
	// Here we call ft_print and give it a function as parameter.
	ft_printf("This is some number %d, print it", flags, &data1);
	printf("\n");
	ft_printf("This is some text %s, print it", flags, data3);
	printf("\n");

	return (0);
}
