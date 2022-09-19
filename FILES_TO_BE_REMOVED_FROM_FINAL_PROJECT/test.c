#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

int	main()
{
	char *s = malloc(sizeof(char) * 5);
	s = "abcd";

	printf("%c\n",*s++);
	printf("%c\n",*s);
	printf("%c\n",*--s);
  
	//(*str)++ dereferences and increments the value by one.
	printf("%c\n",*s+ 1);
	printf("%c\n",*s);
	printf("%c\n",(*s) - 1);

	return (0);
}

