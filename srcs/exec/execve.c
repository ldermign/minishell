/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:31:22 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/15 15:42:25 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_execve(t_struct *ms, char **cmd)
{
	char	*str_path;

	str_path = working_path(ms->env.path, cmd[0]);
	if (execve(str_path, cmd, ms->env.env_bash) == -1)
	{
		printf("minishell: %s: command not found\n", cmd[0]);
		g_sig_error = 127;
		// creer fonction qui close all
		// freeetoutbalalandls
		exit (127); // revoir l'exit
	}
	g_sig_error = 0;
	return (0);
}

void	execute_cmd2(t_struct *ms, t_args *stack)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		g_sig_error = 127;
		perror("fork");
		return ;
	}
	signal(SIGINT, handle_signal_child);
	signal(SIGQUIT, handle_signal_child);
	if (pid > 0)
	{
		ms->pid = pid;
		waitpid(pid, &status, 0);
	}
	else
		cmd_execve(ms, stack->arg_to_pass);
	g_sig_error = 0;
}
