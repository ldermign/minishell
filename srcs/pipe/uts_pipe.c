/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:42:56 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/31 14:51:42 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd_pipe_child_2(t_pipe *pipex)
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
		close_fd_pipe_child_2(pipex);
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
				perror("pipe() failed");
				g_sig_error = 127;
				return (EXIT_FAILURE);
			}
		}
		else
		{
			if (pipe(pipex->fd1) == -1)
			{
				perror("pipe() failed");
				g_sig_error = 127;
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}
