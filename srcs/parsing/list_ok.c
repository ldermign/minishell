/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:28:49 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/02 18:22:29 by ejahan           ###   ########.fr       */
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
