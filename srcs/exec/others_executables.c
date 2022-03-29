/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_executables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 09:45:28 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/29 15:04:23 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_new_executable(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && str[i] == '.')
	{
		if (str[i + 1] && str[i + 1] == '/')
			return (1);
		else
			return (2);
	}
	if (str[i] && str[i] == '/')
		return (3);
	return (-1);
}

int	other_executable(t_struct *ms, t_args *cmd)
{
	int			status;
	pid_t		pid;
	char		**new_env;

	status = 0;
	new_env = get_new_env(ms->env.env_ms);
	// fprintf(stderr, "LA !\n");
	// si pas path, voir si ./ / ou a.out fonctionnent
	pid = fork();
	if (pid == -1)
	{
		//	free
		g_sig_error = 127;
		return (g_sig_error);
	}
	signal(SIGINT, handle_signal_child);
	signal(SIGQUIT, handle_signal_child);
	if (pid > 0)
	{
		ms->pid = pid;
		if (waitpid(pid, &status, 0) == -1)
			perror("waitpid() failed\n");
		if (WIFEXITED(status))
			g_sig_error = WEXITSTATUS(status);
	}
	else
	{
		if (execve(cmd->arg_to_pass[0], cmd->arg_to_pass, new_env) == -1)
		{
			// fprintf(stderr, "new --> errno = %d\n", errno);
			free_env_ms(ms->env.env_ms);
			ft_free_tab_char(new_env);
			if (errno == 13)
				fprintf(stderr, "minishell: %s: Is a directory\n", cmd->arg_to_pass[0]);
			else
				fprintf(stderr, "minishell: %s: command not found\n", cmd->arg_to_pass[0]);
			if (errno == 13)
				g_sig_error = 126;
			else
				g_sig_error = 127;
			exit (g_sig_error);
		}
	}
	ft_free_tab_char(new_env);
	return (0);
}
