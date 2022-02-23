/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:46:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/23 16:14:54 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	there_is_pipe(t_struct *ms, char *prompt)
{	// ici !!! trouver le path
	int		i;
	int		status;
	int		pid;
	int		pipe_fd[2];
	char	**cmd_pipe;

	i = 0;
	status = 0;
	pid = fork();
	if (pid == -1)
	{
		sig_error = 127;
		perror("fork");
		return ;
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return ;
	}
	cmd_pipe = ft_split(prompt, '|');
	print_tab_char(cmd_pipe);
	if (pid > 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		if (execve(path, exec_args_only, env) == -1)
		{
			printf("minishell: %s: command not found\n", args[0]);
			sig_error = 127;
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			close_all_fd(&(ms->std));
			return ;
		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	close_all_fd(&(ms->std));
	sig_error = 0;
}