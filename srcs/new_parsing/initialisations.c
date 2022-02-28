/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:55:27 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/22 00:05:27 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parsing(t_parsing *parsing)
{
	parsing->error = 0;
	parsing->result = NULL;
	parsing->i_line = 0;
	parsing->option = 0;
	parsing->red1 = 0;
	parsing->red2 = 0;
	parsing->nb_pipe = 0;
	parsing->nb_arg = 0;
}

t_list_arg	*init_args(void)
{
	t_list_arg	*list;

	list = malloc(sizeof(*list));
	if (list == NULL)
		return (NULL);
	// list->first->arg_to_pass = NULL;
	list->first = NULL;
	return (list);
}