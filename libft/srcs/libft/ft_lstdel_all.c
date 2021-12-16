/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:16:10 by ldermign          #+#    #+#             */
/*   Updated: 2021/10/05 14:16:11 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_all(t_list *alst)
{
	t_list	*tmp;

	if (!alst)
		return ;
	while (alst != NULL)
	{
		tmp = alst;
		alst = alst->next;
		free(tmp);
	}
	free(alst);
}
