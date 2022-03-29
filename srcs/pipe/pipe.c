/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:46:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/29 10:27:54 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_fork(int *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		g_sig_error = 127;
		return (-1);
	}
	return (1);
}

void	close_fd_pipe_child(t_pipe *pipex)
{
	if (pipex->cmd_nbr == 0)
	{
		close(pipex->fd0[0]);
		if (dup2(pipex->fd0[1], STDOUT_FILENO) < 0)
			perror("dup2");
		close(pipex->fd0[1]);
	}
	else if (pipex->cmd_nbr % 2 == 0)
	{
		if (dup2(pipex->fd1[0], STDIN_FILENO) < 0)
			perror("dup2");
		close(pipex->fd1[0]);
		if (pipex->cmd_nbr != pipex->pipe_tot)
		{
			close(pipex->fd0[0]);
			if (dup2(pipex->fd0[1], STDOUT_FILENO) < 0)
				perror("dup2");
			close(pipex->fd0[1]);
		}
	}
	else
	{
		if (dup2(pipex->fd0[0], STDIN_FILENO) < 0)
			perror("dup2");
		close(pipex->fd0[0]);
		if (pipex->cmd_nbr != pipex->pipe_tot)
		{
			close(pipex->fd1[0]);
			if (dup2(pipex->fd1[1], STDOUT_FILENO) < 0)
				perror("dup2");
			close(pipex->fd1[1]);
		}
	}
}

void	close_fd_pipe_main(t_pipe *pipex)
{
	if (pipex->cmd_nbr == 0)
		close(pipex->fd0[1]);
	else if (pipex->cmd_nbr % 2 == 0)
	{
		close(pipex->fd1[0]);
		if (pipex->cmd_nbr != pipex->pipe_tot)
			close(pipex->fd0[1]);
	}
	else if (pipex->cmd_nbr % 2 != 0)
	{
		close(pipex->fd0[0]);
		if (pipex->cmd_nbr != pipex->pipe_tot)
			close(pipex->fd1[1]);
	}
}

int	pipe_the_good_one(t_pipe *pipex)
{
	if (pipex->cmd_nbr != pipex->pipe_tot)
	{
		if (pipex->cmd_nbr % 2 == 0)
		{
			if (pipe(pipex->fd0) == -1)
			{
				perror("pipe fd0");
				return (EXIT_FAILURE);
			}
		}
		else
		{
			if (pipe(pipex->fd1) == -1)
			{
				perror("pipe fd1");
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}

void	there_is_pipe(t_struct *ms)
{
	t_execute	exec;
	t_args		*stack;
	int			last;
	int			i;

	stack = ms->args->first;
	ms->pipex = malloc(sizeof(t_pipe));
	if (ms->pipex == NULL)
		return ;
	init_struct_pipe(ms->pipex, ms);
	while (stack)
	{
		last = max(last_left(stack->command), last_right(stack->command));
		init_struct_std(stack, &(*ms).std, last);
		if (stack->arg_to_pass)
			init_struct_execute(ms, &exec, stack->arg_to_pass);
		if (pipe_the_good_one(ms->pipex) == EXIT_FAILURE)
		{
			perror("pipe() failed\n");
			g_sig_error = 127;
			exit (g_sig_error); // pas le bon chiffre
		}
		ms->pipex->nbr_exec++;
		if (init_fork(&(ms->pipex->pid)) == -1)
		{
			perror("fork");
			return ;
		}
		if (ms->pipex->pid == 0)
		{
			close_fd_pipe_child(ms->pipex);
			if (ms->std.which == 4 || (stack->redir && stack->redir[0] != NULL))
			{
				free(ms->pipex);
				exit (redirection(ms, stack, ms->pipex));
			}
		}
		else
			close_fd_pipe_main(ms->pipex);
		if (ms->pipex->pid == 0)
		{
			if (is_new_executable(stack->command) != -1)
				other_executable(ms, stack);
			else if (stack->arg_to_pass && is_built_in(stack->arg_to_pass[0]) == EXIT_FAILURE)
				exit (execute_cmd_execve(ms, &exec, stack->arg_to_pass));
			else if (stack->arg_to_pass)
			{
				ft_free_struct_execute(&exec);
				built_in(ms, stack);
				free_list(ms->args);
				ft_free_all(ms);
			}
			free(ms->pipex);
			exit (g_sig_error);
		}
		if (stack->arg_to_pass)
			ft_free_struct_execute(&exec);
		stack = stack->next;
		ms->pipex->cmd_nbr++;
		ms->pipex->pipe++;
	}
	i = 0;
	int	status= 0;
	while (ms->pipex->nbr_exec > 0)
	{
		if (waitpid(i, &status, 0) == -1)
			perror("waitpid() failed\n");
		if (WIFEXITED(status))
			g_sig_error = WEXITSTATUS(status);
		ms->pipex->nbr_exec--;
	}
	free(ms->pipex);
}
