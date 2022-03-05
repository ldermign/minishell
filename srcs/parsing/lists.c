/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 17:12:59 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/05 06:08:44 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	insertion(t_list_arg *list, char *new_arg)
{
	t_args	*new;

	if (list == NULL)
		return (-1);
	new = malloc(sizeof(*new));
	if (new == NULL)
		return (-1);
	new->command = new_arg;
	new->next = list->first;
	list->first = new;
	return (0);
}

int	delete(t_list_arg *list)
{
	t_args	*to_delete;

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

void	print_list(t_list_arg *list)
{
	t_args	*args;

	args = list->first;
	if (list == NULL)
		return ;
	printf("\nlist :\n");
	while (args != NULL)
	{
		printf("\033[1;35m[%s]\n\033[0m", args->command);
		args = args->next;
	}
	printf("\n");
}
