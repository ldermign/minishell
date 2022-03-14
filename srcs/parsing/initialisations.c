/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:55:27 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/14 04:53:16 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parsing(t_parsing *parsing)
{
	parsing->error = 0;
	parsing->i_line = 0;
	parsing->option = 0;
	parsing->nb_pipe = 0;
	parsing->nb_arg = 0;
	parsing->quotes = 0;
	parsing->len_arg = 0;
	parsing->fill_arg = 0;
	parsing->result = NULL;
}

t_list_arg	*init_args(void)
{
	t_list_arg	*list;

	list = malloc(sizeof(*list));
	if (list == NULL)
		return (NULL);
	list->first = NULL;
	return (list);
}

t_list_hd	*init_here_doc(void)
{
	t_list_hd	*list;

	list = malloc(sizeof(*list));
	if (list == NULL)
		return (NULL);
	list->first = NULL;
	return (list);
}
