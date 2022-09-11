#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <libft.h>

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

int	main()
{
	printf("%d\n", is_flag('a'));
	printf("%d\n", is_flag('b'));
	printf("%d\n", is_flag('c'));
	printf("%d\n", is_flag('d'));
	printf("%d\n", is_flag('-'));
	printf("%d\n", is_flag('+'));
	printf("%d\n", is_flag(' '));
	printf("%d\n", is_flag('#'));
	printf("%d\n", is_flag('0'));
	return (0);
}