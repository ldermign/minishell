/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:40:54 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/10 11:46:23 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_cmds_pompt(t_args *stack)
{
	t_args	*tmp;

	if (stack == NULL)
		return ;
	while (stack)
	{
		tmp = stack;
		ft_free_tab(stack->redir);
		free(stack->command);
		ft_free_tab(stack->arg_to_pass);
		stack = stack->next;
		free(tmp);
	}
}