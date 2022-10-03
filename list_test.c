#include <stdio.h>
#include <stdlib.h>

typedef struct s_params
{
	int		id;
	char 	*flags;
	int		width;
	int		precision;
	char	*length;
	char	conversion;

} t_params;

typedef struct s_plist
{
    t_params            params;
    struct s_plist        *next;
} t_plist;

void	REMOVE_data_printer(t_params *params, int state)
{
	printf("\n\nid:\t\t%d\n", params->id);
	printf("\n\nflags:\t\t%s\n", params->flags);
	printf("width:\t\t%d\n", params->width);
	printf("precision:\t%d\n", params->precision);
	printf("length:\t\t%s\n", params->length);
	printf("conversion:\t%c\n", params->conversion);

	printf("state: %d\n\n", state);
}

void	initialize_params(t_params *params)
{
	params->id = 0;
    params->flags = (char *)malloc(sizeof(char) * 8);
    params->width = 0;
    params->precision = 0;
    params->length = (char *)malloc(sizeof(char) * 3);
    params->conversion = 0;
}

t_plist	*init_plist()
{
    t_params    params;
    t_plist        *list;

	list = malloc(sizeof(t_plist)); 
    initialize_params(&params);
    list->params = params;
    list->next = NULL;

    return (list);
}

t_plist	*add_t_params(t_plist *start)
{
    t_params    params;
    t_plist     *current;
    t_plist     *new;
	int			id;

    current = start;
    while(current->next)
        current = current->next;
    id = current->params.id;
	id++;
	new = init_plist();
    current->next = new;
    initialize_params(&params);
    new->params = params;
    new->next = NULL;
	new->params.id = id;

    return (start);
}

// void	destroy_list(t_plist *start)
// {
// 	t_plist *next;

// 	while (next)
// 	{
// 		next = start->next;
// 		free(start);
// 	}
// }

int main() {

t_plist *list;

list = init_plist();
list = add_t_params(list);
list = add_t_params(list);
list = add_t_params(list);
list = add_t_params(list);
list = add_t_params(list);
list = add_t_params(list);
list = add_t_params(list);
list = add_t_params(list);

t_plist	*start;
start = list;

while(start)
{
	REMOVE_data_printer(&(start->params),1);
	start = start->next;
}

destroy_list(list);

}