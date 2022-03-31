/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:40:54 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/31 11:15:28 by ldermign         ###   ########.fr       */
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
		stack = stack->next;
		free(tmp->var);
		free(tmp);
	}
	free(stack);
}

void	ft_free_tab_char(char **tabl)
{
	int	i;

	i = 0;
	if (tabl == NULL)
		return ;
	while (tabl[i])
	{
		free(tabl[i]);
		i++;
	}
	free(tabl);
}

void	ft_free_struct_execute(t_execute *exec)
{
	ft_free_tab_char(exec->new_env);
	ft_free_tab_char(exec->paths);
	if (exec->str_path != NULL)
		free(exec->str_path);
}

void	ft_free_all(t_struct *ms)
{
	free_env_ms(ms->env.env_ms);
}
