/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:28:49 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/12 03:13:33 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_arg	*reverse_list(t_list_arg *list)
{
	t_list_arg	*ret;

	ret = init_args();
	while (list->first != NULL)
	{
		insertion(ret, list->first->command);
		delete(list);
	}
	free(list);
	return (ret);
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
