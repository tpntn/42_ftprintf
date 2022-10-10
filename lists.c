/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:59:55 by tpontine          #+#    #+#             */
/*   Updated: 2022/10/03 12:03:54 by tpontine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	t_params	params;
	t_plist		*list;

	list = malloc(sizeof(t_plist)); 
	initialize_params(&params);
	list->params = params;
	list->next = NULL;

	return (list);
}

t_plist	*add_t_params(t_plist *start)
{
	t_params	params;
	t_plist		*current;
	t_plist		*new;
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