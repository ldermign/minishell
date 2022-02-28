/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:28:49 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/28 17:59:24 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new_list(t_list *list)
{
	// t_args	*tmp;
	t_args	*new;
	t_list	*ret;

	// ret->first = list->first;
	ret->first = NULL;
	while (list->first != NULL)
	{
		new = list->first;
		new->next = ret->first;
		ret->first = new;
		list->first = list->first->next;
		
		// new = list->first;
		// ret->first->next = tmp;
		// tmp = ret->first;
		
		// list->first = list->first->next;
		// ret->first->next = list->first;
		// ret->first = ret->first->next;
	}
	return (ret);
}
