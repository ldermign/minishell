/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:28:49 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/28 19:05:32 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_arg	*new_list(t_list_arg *list)
{
	t_args		*new;
	t_list_arg	*ret;

	ret = init_args();
	print_list(list);
	while (list->first != NULL)
	{
		new = list->first;
		new->next = ret->first;
		list->first = list->first->next;
		ret->first = new;
		// printf("test -> [%s]\n", list->first->command);
	}
	return (ret);
}
