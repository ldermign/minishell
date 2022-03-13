/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 06:07:10 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/12 07:40:32 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_arg_to_pass(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

static void	free_redir(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

int	free_list(t_list_arg *list)
{
	t_args	*to_delete;

	if (list == NULL)
		return (-1);
	while (list->first != NULL)
	{
		if (list->first->arg_to_pass != NULL)
			free_arg_to_pass(list->first->arg_to_pass);
		if (list->first->redir != NULL)
			free_redir(list->first->redir);
		if (list->first->command != NULL)
			free(list->first->command);
		free_list_hd(list->first->here_doc);
		to_delete = list->first;
		list->first = list->first->next;
		free(to_delete);
	}
	free(list);
	return (0);
}

int	free_list2(t_list_arg *list)
{
	int		i;
	t_args	*to_delete;

	if (list == NULL)
		return (-1);
	while (list->first != NULL)
	{
		i = 0;
		if (list->first->command != NULL)
			free(list->first->command);
		free_list_hd(list->first->here_doc);
		to_delete = list->first;
		list->first = list->first->next;
		free(to_delete);
	}
	free(list);
	return (0);
}

int	free_list3(t_list_arg *list)
{
	int		i;
	t_args	*to_delete;

	if (list == NULL)
		return (-1);
	while (list->first != NULL)
	{
		i = 0;
		free_list_hd(list->first->here_doc);
		if (list->first->arg_to_pass != NULL)
			free_arg_to_pass(list->first->arg_to_pass);
		if (list->first->command != NULL)
			free(list->first->command);
		to_delete = list->first;
		list->first = list->first->next;
		free(to_delete);
	}
	free(list);
	return (0);
}
