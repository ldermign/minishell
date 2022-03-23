/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:40:54 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/23 02:55:12 by ejahan           ###   ########.fr       */
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

void	free_env_ms(t_env_ms *stack)
{
	t_env_ms	*tmp;

	if (stack == NULL)
		return ;
	while (stack)
	{
		tmp = stack;
		free(stack->var);
		stack = stack->next;
		free(tmp);
	}
}

void	ft_free_tab_char(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i])
	{
		free(tabl[i]);
		i++;
	}
}
