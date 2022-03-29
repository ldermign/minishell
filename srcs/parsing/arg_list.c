/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 05:42:28 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/29 10:00:56 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_arg_list(t_list_hd *hd)
{
	int			i;
	t_here_doc	*tmp;

	i = 0;
	tmp = hd->first;
	while (hd->first != NULL)
	{
		i++;
		hd->first = hd->first->next;
	}
	hd->first = tmp;
	return (i);
}

char	**arg_list(t_list_hd *hd, t_struct *minish)
{
	char		**ret;
	t_here_doc	*tmp;
	int			i;

	tmp = hd->first;
	i = nb_arg_list(hd);
	ret = malloc(sizeof(char *) * (i + 1));
	if (ret == NULL)
	{
		minish->parsing.error = 1;
		fprintf(stderr, "ERROR MALLOC\n");
		return (NULL);
	}
	ret[i] = NULL;
	i = 0;
	while (hd->first != NULL)
	{
		ret[i] = hd->first->here_doc;
		i++;
		hd->first = hd->first->next;
	}
	hd->first = tmp;
	return (ret);
}
