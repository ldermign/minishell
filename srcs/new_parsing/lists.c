/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 17:12:59 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/11 18:07:01 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*init(int i)
{
	t_list		*list;

	(void)i;
	list = malloc(sizeof(*list));
	if (list == NULL)
		return (NULL);
	list->first = NULL;
	return (list);
}

int	insertion(t_list *list, int new_nbr)
{
	t_element	*new;

	if (list == NULL)
		return (-1);
	new = malloc(sizeof(*new));
	if (new == NULL)
		return (-1);
	new->nbr = new_nbr;
	new->next = list->first;
	list->first = new;
	return (0);
}

int	delete(t_list *list)
{
	t_element	*to_delete;

	if (list == NULL)
		return (-1);
	if (list->first != NULL)
	{
		to_delete = list->first;
		list->first = list->first->next;
		free(to_delete);
	}
	return (0);
}

int	free_list(t_list *list)
{
	t_element	*to_delete;

	if (list == NULL)
		return (-1);
	while (list->first != NULL)
	{
		to_delete = list->first;
		list->first = list->first->next;
		free(to_delete);
	}
	free(list);
	return (0);
}