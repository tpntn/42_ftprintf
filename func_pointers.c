#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <libft.h>

// gcc func_pointers.c -I Libft/ -L libft -lft

void	ft_printf(const char *str, ...);

char	*initialize_sequence(int size, int addition) //size + add bytes
{
	int		i;
	char	*sequence;

	if (size < 0)
		size *= -1;
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

	i = 0;
	while (*(num + i) && *((*addto + i)))
		i++;
	i--;

	// while (*(*addto + i) != '.' && *(num + i) != '.')
	while (i > 1)
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

void	multiplyer(char **s, int multiplyer, int len)
{
	int		i;
	char	memo = 48;
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

char *count_fraction(int exp)
{
	char *seq;
	char *result;
	int	i;
	int c = 0;

	if (exp == 0)
	{
		// printf("1.0");
		return ("1.0");
	}
		
	if (exp < 0)
		exp *= -1;

	i = exp + 1;

	seq = initialize_sequence(exp,2);
	seq[exp+1] = '1';
	while (c < exp)
	{
		multiplyer(&seq, 5, exp+2);
		c++;
	}
	seq[1] = '.';
	// printf("%s\n", seq);
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

char	*count_integer(int exp)
{
	int		i;
	char	*result;

	result = initialize_sequence(40,0);
	result[39] = '1';

	i = 0;
	while (i < exp)
	{
		multiplyer(&result,2,40);
		i++;
	}
	return (result);
}

void	ft_float_to_ascii(float f)
{
	int	*p;
	int	i;
	int	c;
	int	exp;
	char *manchar;
	char *result_frac;
	char *result_int;
	
	exp = ret_exp(f);
	result_frac = initialize_sequence(exp - 23,3);
	result_int = initialize_sequence(40,1);
	result_frac[1] = '.';

	p = (int *)&f;
	i = 0;
	c = 23;
	
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
			}
			else
			{
				// printf("counting with:%d\n",exp-c);
				manchar = count_integer(exp - c);
				adder(&result_int,manchar);
				// printf("adding bit%d:\t%s\n", i+1, manchar);
				// printf("result:\t\t%s\n", result_int);
			}
			ft_bzero(manchar, ft_strlen(manchar));
			ft_strdel(&manchar);
		}	
		c--;	
		i++;
	}
	printf("%d\n",exp);
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
		ft_putstr(result_int+i);
	else
		ft_putchar('0');
	i = 0;
	c = 1;
	while (*(result_frac + i))
		i++;
	while (c < i)
		ft_putchar(*(result_frac + c++));
	
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

void	ft_printf(const char *str, ...)
{
	int		c;
	va_list	data;
	int		STATE;
	
	STATE = 0;
	va_start(data, str);
	while (*str)
	{
		if (*str == '%')
		{
			STATE = 1;
			str++;
			while (!is_type_specifier(*str) && STATE != 0)
			{
				if (*str == '%')
				{
					ft_putchar(*str);
					break;
				}
				if (*str == '$')
					printf("ok");
					// parse_params(str); //increment str++ after calling the function?
				// if (is_flag(str))
				// 	parse_flags(str);
				str++;
			}
			if (STATE != 0)
			{
				c = 0;
				while (c < 10)
				{
					if (types[c].id == *str)
						types[c].func(data);
					c++;
				}
			}
			
			
		}
		else 
			ft_putchar(*(str));
		str++;
	}
	va_end(data);
}


int main()
{
	// float f = 104857.601562;
	// float f = 1.17549435082e-38; //ei toimi
	// float f = 0.1;
	// float f = 1.0e38; //lähellä maksia???
	// float f = 1.5e-37; //tämä on viimeinen joka toimii.... -38 ei toimi enää
	float f = -1.0e-37;

	// printf("%.146f\n",f);
	// ft_float_to_ascii(f);
	// ft_printf("\n");
	ft_printf("%s %s %d\n","hello world", "again", 1);
	ft_printf("%d\n",123);
	ft_printf("%%\n");
	ft_printf("%$2\n");
	

	return (0);
}