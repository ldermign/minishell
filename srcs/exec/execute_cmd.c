/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:10:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/28 20:57:05 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_fd(t_red_std *std)
{
	if (std->fd_to_read != 0)
		close(std->fd_to_read);
	if (std->fd_to_write != 0)
		close(std->fd_to_write);
}

static void	both_redirections(t_red_std *std, char **args)
{
	std->fd_to_read = open(args[std->last_left + 1], O_RDONLY, 0644);
	if (std->which == 1)
		std->fd_to_write = open(std->name_file, O_WRONLY | O_TRUNC, 0644);
	else
		std->fd_to_write = open(std->name_file, O_WRONLY | O_APPEND, 0644);
	dup2(std->fd_to_read, 0);
	dup2(std->fd_to_write, 1);
}

int	get_good_fd_built_in(char **args, char *name_file, t_red_std *std)
{
	char	*line;

	std->name_file = name_file;
	if (std->which == -1)
		return (EXIT_SUCCESS);
	if (std->both == 0)
	{
		if (std->which == 1)
			std->fd_to_write = open(std->name_file, O_WRONLY | O_TRUNC, 0644);
		else if (std->which == 3)
			std->fd_to_write = open(std->name_file, O_WRONLY | O_APPEND, 0644);
		if (std->which == 1 || std->which == 3)
			dup2(std->fd_to_write, 1);
		if (std->which == 2)
		{
			std->fd_to_read = open(args[std->last_left + 1], O_RDONLY);
			dup2(std->fd_to_read, 0);
		}
		else if (std->which == 4)
		{
			line = readline("> ");
			while (ft_strcmp(line, args[std->last_left + 1]) != 0)
				line = readline("> ");
		}
		if (std->which == 4)
			dup2(std->fd_to_read, 0);
	}
	else if (std->both == 1)
		both_redirections(std, args);
	if (std->fd_to_write == -1 || std->fd_to_read == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_good_fd(char **args, char *name_file, t_red_std *std, int pipefd[])
{
	char	*line;

	std->name_file = name_file;
	if (std->which == -1)
		return (EXIT_SUCCESS);
	if (std->both == 0)
	{
		if (std->which == 1)
			std->fd_to_write = open(std->name_file, O_WRONLY | O_TRUNC, 0644);
		else if (std->which == 3)
			std->fd_to_write = open(std->name_file, O_WRONLY | O_APPEND, 0644);
		if (std->which == 1 || std->which == 3)
			dup2(std->fd_to_write, 1);
		if (std->which == 2)
		{
			std->fd_to_read = open(args[std->last_left + 1], O_RDONLY);
			dup2(std->fd_to_read, 0);
		}
		else if (std->which == 4)
		{
			line = readline("> ");
			while (ft_strcmp(line, args[std->last_left + 1]) != 0)
			{
				write(pipefd[1], line, ft_strlen(line));
				write(pipefd[1], "\n", 1);
				line = readline("> ");
			}
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[1]);
		}
	}
	else if (std->both == 1)
		both_redirections(std, args);
	if (std->fd_to_write == -1 || std->fd_to_read == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	execute_cmd(t_struct *ms, char *path, char **args, char **exec_args_only, char **env)
{
	int		status;
	pid_t	pid;
	int		pipefd[2];

	status = 0;
	pid = fork();
	ms->pid = pid;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	if (pid == -1)
	{
		sig_error = 127;
		perror("fork");
		return ;
	}
	if (pid > 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		get_good_fd(args, ms->std.name_file, &(ms->std), pipefd);
		if (execve(path, exec_args_only, env) == -1)
		{
			printf("minishell: %s: command not found\n", args[0]);
			sig_error = 127;
			close(pipefd[0]);
			close(pipefd[1]);
			close_all_fd(&(ms->std));
			return ;
		}
		close(pipefd[0]);
		close(pipefd[1]);
	}
	close_all_fd(&(ms->std));
	sig_error = 0;
}

