/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:40:54 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/23 15:44:23 by ldermign         ###   ########.fr       */
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
	free(exec->str_path);
}

void	ft_free_all(t_struct *ms)
{
	// free(ms->prompt);
	free(ms->env.env_bash);
	free_env_ms(ms->env.env_ms);
}

// ==741560== 13 bytes in 1 blocks are still reachable in loss record 7 of 80
// ==741560==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==741560==    by 0x40199B: create_path (execve.c:25)
// ==741560==    by 0x401B0B: working_path (execve.c:55)
// ==741560==    by 0x40590C: init_struct_execute (init_struct.c:61)
// ==741560==    by 0x405D2D: there_is_pipe (pipe.c:118)
// ==741560==    by 0x40131B: command (main.c:29)
// ==741560==    by 0x4014FB: loop (main.c:61)
// ==741560==    by 0x4015D0: main (main.c:84)
