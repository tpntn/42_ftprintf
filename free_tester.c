#include "libft.h"

void	append_string(char **s1, char *s2, int end)
{
	char	*temp;
	
	if (end)
		temp = ft_strjoin(s2, *s1);
	else
		temp = ft_strjoin(*s1, s2);
	free(*s1);
	*s1 = ft_strdup(temp);
	free(temp);
}

void	modify(char **s)
{
	int		i;
	char*	temp;
	
	i = 0;
	while(*(*s + i))
		*(*s + i++) += 1;

	temp = ft_strjoin(*s, "def");
	free(*s);
	*s = ft_strdup(temp);
	free(temp);
}

void	modfunc(char **s)
{
	modify(s);
}
	

int	main()
{
	char *a = malloc(sizeof(char) * 4);
	a = ft_strcpy(a, "abc");

	append_string(&a, "123", 0);

	ft_putstr(a);

	free(a);

	return (0);
}