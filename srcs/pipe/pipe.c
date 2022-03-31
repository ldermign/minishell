/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:46:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/31 15:00:40 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_for_the_end(t_struct *ms)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (ms->pipex->nbr_exec > 0)
	{
		if (waitpid(i, &status, 0) == -1)
			perror("waitpid() failed\n");
		if (WIFEXITED(status))
			g_sig_error = WEXITSTATUS(status);
		ms->pipex->nbr_exec--;
	}
	if (ms->pipex != NULL)
		free(ms->pipex);
}

static void	handle_child(t_struct *ms, t_args *stack, t_execute *exec)
{
	close_fd_pipe_child(ms->pipex);
	if (ms->std.which == 4 || (stack->redir && stack->redir[0] != NULL))
	{
		free(ms->pipex);
		ft_free_struct_execute(exec);
		exit (redirection(ms, stack));
	}
	if (is_new_executable(stack->command) != -1)
		other_executable(ms, stack);
	else if (stack->arg_to_pass
		&& is_built_in(stack->arg_to_pass[0]) == EXIT_FAILURE)
		exit (execute_cmd_execve(ms, exec, stack->arg_to_pass));
	else if (stack->arg_to_pass)
	{
		ft_free_struct_execute(exec);
		built_in(ms, stack);
		free_list(ms->args);
		ft_free_all(ms);
	}
	free(ms->pipex);
	exit (g_sig_error);
}

static void	boucle(t_struct *ms, t_args *stack, t_execute *exec)
{
	int	last;

	while (stack)
	{
		last = max(last_left(stack->command),
				last_right(stack->command));
		init_struct_std(stack, &(*ms).std, last);
		if (stack->arg_to_pass)
			init_struct_execute(ms, exec, stack->arg_to_pass);
		if (pipe_the_good_one(ms->pipex) == EXIT_FAILURE)
			exit (g_sig_error);
		ms->pipex->nbr_exec++;
		if (init_fork(&(ms->pipex->pid)) == -1)
			return ;
		if (ms->pipex->pid == 0)
			handle_child(ms, stack, exec);
		else
			close_fd_pipe_main(ms->pipex);
		if (stack->arg_to_pass)
			ft_free_struct_execute(exec);
		stack = stack->next;
		ms->pipex->cmd_nbr++;
	}
}

void	there_is_pipe(t_struct *ms)
{
	t_execute	exec;
	t_args		*stack;

	stack = ms->args->first;
	ms->pipex = malloc(sizeof(t_pipe));
	if (ms->pipex == NULL)
		return ;
	init_struct_pipe(ms->pipex, ms);
	boucle(ms, stack, &exec);
	wait_for_the_end(ms);
}
