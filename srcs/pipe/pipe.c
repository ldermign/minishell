/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:46:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/26 18:37:08 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_fork(int *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		sig_error("fork", 127);
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
	int			i;

	stack = ms->args->first;
	ms->pipex = malloc(sizeof(t_pipe));
	if (ms->pipex == NULL)
		return ;
	init_struct_pipe(ms->pipex, ms);
	while (stack)
	{
		// fprintf(stderr, "%s\n", stack->arg_to_pass[0]);
		if (stack->arg_to_pass)
			init_struct_execute(ms, &exec, stack->arg_to_pass);
		if (pipe_the_good_one(ms->pipex) == EXIT_FAILURE)
			exit (127); // pas le bon chiffre
		ms->pipex->nbr_exec++;
		if (init_fork(&(ms->pipex->pid)) == -1)
		{
			perror("fork");
			return ;
		}
		if (ms->pipex->pid == 0)
		{
			close_fd_pipe_child(ms->pipex);
			if (stack->redir != NULL)
				exit (redirection(ms, stack, ms->pipex));
		}
		else
			close_fd_pipe_main(ms->pipex);
		if (ms->pipex->pid == 0)
		{
			if (stack->arg_to_pass && is_built_in(stack->arg_to_pass[0]) == EXIT_FAILURE)
				exit (execute_cmd_execve(ms, &exec, stack->arg_to_pass));
			else if (stack->arg_to_pass)
			{
				ft_free_struct_execute(&exec);
				built_in(ms, stack);
				ft_free_all(ms);
			}
			free(ms->pipex);
			exit (sig_error(NULL, 0));
		}
		if (stack->arg_to_pass)
			ft_free_struct_execute(&exec);
		stack = stack->next;
		ms->pipex->cmd_nbr++;
		ms->pipex->pipe++;
	}
	i = 0;
	while (i < ms->pipex->nbr_exec)
	{
		wait(NULL);
		i++;
	}
	free(ms->pipex);
}
