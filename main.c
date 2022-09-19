/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:18:25 by tpontine          #+#    #+#             */
/*   Updated: 2022/09/19 10:55:34 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// gcc func_pointers.c -I Libft/ -L libft -lft

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

void ft_foo(va_list data)
{
	int a = va_arg(data, int);
	ft_putnbr(a);
}

void ft_print_str(va_list data)
{
	char *str = va_arg(data, char*);
	ft_putstr(str);
}

// This creates a type "printer", which is a pointer to functions that takes a va_list and returns nothing.
typedef void (*printer)(va_list data);

typedef struct s_type
{
	char	id;
	printer func;
} t_type;

static t_type types[] = {
			{'d', ft_foo},
			{'s', ft_print_str}
	};

int	is_type_specifier(char str)
{
	char *types = "csdioxXuFfeEaAgGnp";
	while (*types)
	{
		if (*types == str)
			return (1);
		types++;
	}
	return (0);
}

void parse_params(const char *str)
{
	// str++;
	// while(ft_isdigit(*str))
	// {
		printf("ok");
	// 	str++;
	// }
}

typedef struct s_params
{
	char 	flags;
	int		width;
	int		precision;
	int		length;
	char	*conversion;

} t_params; 

#define STATE_NORMAL		0
#define STATE_FLAGS			1
#define STATE_WIDTH			2
#define STATE_PRECISION		3
#define	STATE_LENGTH		4
#define	STATE_CONVERSION	5

int		is_flag(char c)
{
	const char flags[] = "-+ #0";
	int i;

	i = 0;
	while (flags[i])
	{
		if (flags[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	flags_handler(char c, int *state, t_params *params)
{
	if (is_flag(c))
		params->flags = c;
	*state = STATE_WIDTH;
}



void	width_handler(char c, int *state, t_params *params)
{
	//this handles the width and set the state to next state
	*state = STATE_PRECISION;
}

void	precision_handler(char c, int *state, t_params *params)
{
	//this handles the precision and set the state to next state
	*state = STATE_LENGTH;
}

void	length_handler(char c, int *state, t_params *params)
{
	//this handles the length and set the state to next state
	*state = STATE_CONVERSION;
}

void	conversion_handler(char c, int *state, t_params *params)
{
	//this handles the length and set the state to next state
	*state = STATE_CONVERSION;
}

void	initialize_params(int *state, t_params *params)
{
	//when state == STATE_NORMAL, set start values
	//if state = STATE_CONVERSION clear all values (free etc)
}

void	ft_printf(const char *str, ...)
{
	va_list		data;
	int			state;
	t_params	params;

	state = STATE_NORMAL;
	
	va_start(data, str);
	while (*str)
	{
		if (state == STATE_NORMAL)
		{
			if (*str == '%')
			{
				state = STATE_FLAGS;
				initialize_params(&state, &params);
			}
			else 
				ft_putchar(*str);
		}
		else if (state == STATE_FLAGS)
			flags_handler(*str,&state, &params);
		else if (state == STATE_WIDTH)
			width_handler(*str,&state, &params);
		else if (state == STATE_PRECISION)
			precision_handler(*str,&state, &params);
		else if (state == STATE_LENGTH)
			length_handler(*str,&state, &params);
		else if (state == STATE_CONVERSION)
			conversion_handler(*str,&state, &params);

		// if (*str == '%')
		// {
		// 	str++;
		// 	while (!is_type_specifier(*str) && STATE != 0)
		// 	{
		// 		if (*str == '%')
		// 		{
		// 			ft_putchar(*str);
		// 			break;
		// 		}
		// 		if (*str == '$')
		// 			printf("ok");
		// 			// parse_params(str); //increment str++ after calling the function?
		// 		// if (is_flag(str))
		// 		// 	parse_flags(str);
		// 		str++;
		// 	}
		// 	if (STATE != 0)
		// 	{
		// 		c = 0;
		// 		while (c < 10)
		// 		{
		// 			if (types[c].id == *str)
		// 				types[c].func(data);
		// 			c++;
		// 		}
		// 	}
			
			
		// }
		// else 
		// 	ft_putchar(*(str));
		str++;
	}
	va_end(data);
}


int main()
{
	// float f = 104857.601562;
	// float f = 1.17549435082e-38; //ei toimi
	float f = 0.1;
	// float f = 1.0e38; //lähellä maksia???
	// float f = 1.5e-37; //tämä on viimeinen joka toimii.... -38 ei toimi enää
	// float f = -1.0e-37;

	// printf("%.146f\n",f);
	ft_ftoa(f);
	
	printf("%s %s %d\n","hello world", "again", 1);
	printf("%d\n",123);
	printf("%%\n");

	return (0);
}