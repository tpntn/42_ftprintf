// #include "ft_printf.h"

// // This is a function that takes a function and int as parameters.
// // function pointer format: 
// // 		<return value> (*<name>)(<params>)

// /*
// void ft_print(void (*f)(void), int i)
// {
// 	printf("%d",i);
// 	f(); //This calls the function given as parameter.
// }
// */

// void ft_foo(va_list data)
// {
// 	int a = va_arg(data, int);
// 	ft_putnbr(a);
// }

// void ft_print_str(va_list data)
// {
// 	char *str = va_arg(data, char*);
// 	ft_putstr(str);
// }

// // This creates a type "printer", which is a pointer to functions that takes a va_list and returns nothing.
// typedef void (*printer)(va_list data);

// typedef struct s_type
// {
// 	char	id;
// 	printer func;
// } t_type;

// static t_type types[] = {
// 	{'d', ft_foo},
// 	{'s', ft_print_str}
// };

// int	main()
// {
// 	char *str = "d";
// 	c = 0;
// 	while (c < 10)
// 	{
// 		if (types[c].id == *str)
// 			types[c].func(data);
// 		c++;
// 	}

// 	return (0);
// }

	