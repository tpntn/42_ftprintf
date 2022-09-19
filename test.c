#include <stdio.h>
#include <string.h>

typedef struct s_params
{
    char     *flags;
} t_params;

int main() {

	t_params  data;
	//data.flags = malloc(sizeof(char) * 4);
 	strlcat(data.flags,"1",4);
	printf("%s\n", data.flags);

	strlcat(data.flags,"2",4);

	printf("%s\n",data.flags);
	strlcat(data.flags,"3",4);

	printf("%s\n",data.flags);

  return 0;
}
