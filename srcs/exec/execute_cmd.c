/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:10:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/20 19:18:59 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_good_fd(char **args, char *name_file, t_red_std *std)
{
	char	*line;

	std->name_file = name_file;
	if (std->which == -1)
		return (EXIT_SUCCESS);
	if (std->both == 0)
	{
		if (std->which == 1)
		{
			// printf("par la\n");
			std->fd_to_write = open(std->name_file, O_WRONLY | O_TRUNC, 0644);
		}
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
			while (ft_strcmp(readline("> "), args[std->last_left + 1]) != 0)
				line = readline("> ");
			// reboot_struct_std(std);
			// std->fd_to_read = 1;
			// dup(0);
			// dup2(std->fd_to_read, 0);
		}
	}
	else if (std->both == 1)	//	si les chevrons sont melanges
	{
		std->fd_to_read = open(args[std->last_left + 1], O_RDONLY, 0644);
		if (std->which == 1)
			std->fd_to_write = open(std->name_file, O_WRONLY | O_TRUNC, 0644);
		else
			std->fd_to_write = open(std->name_file, O_WRONLY | O_APPEND, 0644);
		dup2(std->fd_to_read, 0);
		dup2(std->fd_to_write, 1);
	}
	if (std->fd_to_write == -1 || std->fd_to_read == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	close_all_fd(t_red_std *std)
{
	close(std->fd_to_read);
	close(std->fd_to_write);
}

void	execute_cmd(t_struct *ms, char *path, char **args, char **env)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		sig_error = 127;
		perror("fork"); // voir le cas d'erreur
		return ;
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		// printf("c'est cense passer par la\n");
		get_good_fd(args, ms->std.name_file, &(ms->std));
		printf("putain\n");
		if (execve(path, args, env) == -1)
		{
			printf("bash: %s: command not found\n", args[0]);
			sig_error = 127;
		}
		close_all_fd(&(ms->std));
		return ;
	}
	sig_error = 0;
}

