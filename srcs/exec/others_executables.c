/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_executables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 09:45:28 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/23 10:32:24 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_new_executable(char *str)
{
	if (str[0] && str[0] == '.')
	{
		if (str[1] && str[1] == '/')
			return (1);
		else
			return (2);
	}
	if (str[0] && str[0] == '/')
		return (3);
	return (-1);
}

int	other_executable(t_struct *ms, t_args *cmd, char **env_bash)
{
	int		status;
	pid_t	pid;

	status = 0;
	// si pas path, voir si ./ / ou a.out fonctionnent
	pid = fork();
	if (pid == -1)
	{
		//	free
		return (sig_error("fork", 127));
	}
	signal(SIGINT, handle_signal_child);
	signal(SIGQUIT, handle_signal_child);
	if (pid > 0)
	{
		ms->pid = pid;
		waitpid(pid, &status, 0);
	}
	else
	{
		if (execve(cmd->arg_to_pass[0], cmd->arg_to_pass, env_bash) == -1)
		{
			printf("minishell: %s: command not found\n", cmd->arg_to_pass[0]);
			//	free
			exit (sig_error(NULL, 127));
		}
	}

	return (sig_error(NULL, 0));
}
