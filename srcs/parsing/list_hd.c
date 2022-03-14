/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_hd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 08:10:26 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/14 04:56:21 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	insertion_here_doc(t_list_hd *list, char *new_arg)
{
	t_here_doc	*new;

	if (list == NULL)
		return (-1);
	new = malloc(sizeof(*new));
	if (new == NULL)
		return (-1);
	new->here_doc = new_arg;
	new->next = list->first;
	list->first = new;
	return (0);
}

int	delete_hd(t_list_hd *list)
{
	t_here_doc	*to_delete;

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

void	print_list_hd(t_list_hd *list)
{
	t_here_doc	*args;

	args = list->first;
	if (list == NULL)
		return ;
	printf("\nlist :\n");
	while (args != NULL)
	{
		printf("\033[1;35m[%s]\n\033[0m", args->here_doc);
		args = args->next;
	}
	printf("\033[1;35mNULL\n\033[0m");
	printf("\n");
}

t_list_hd	*reverse_list_hd(t_list_hd *list)
{
	t_list_hd	*ret;

	ret = init_here_doc();
	while (list->first != NULL)
	{
		insertion_here_doc(ret, list->first->here_doc);
		delete_hd(list);
	}
	free(list);
	return (ret);
}

int	free_list_hd(t_list_hd *list)
{
	t_here_doc	*to_delete;

	if (list == NULL)
		return (-1);
	while (list->first != NULL)
	{
		to_delete = list->first;
		list->first = list->first->next;
		free(to_delete);
	}
	printf("free hd\n");
	free(list);
	return (0);
}
