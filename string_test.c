#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include "Libft/libft.h"

char *handle_fraction(char *frac)
{
	char *addition = malloc(sizeof(char) * 3);
	addition = strcpy(addition,"00abd\0");
	
	char *new = ft_strjoin(frac,addition);
	printf("%s",new);
	free(frac);
	free(addition);
	*addition = 0;
	return (new);
}

int main() {

  char *s = malloc(sizeof(char)*4);
  s[0] = '0';
  s[1] = '.';
  s[2] = '0';
  s[3] = 0;

  s = handle_fraction(s);
  free(s);
  return 0;
}