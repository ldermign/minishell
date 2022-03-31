/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_executables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 09:45:28 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/31 12:58:02 by ldermign         ###   ########.fr       */
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

static void	handle_child(t_struct *ms, t_args *cmd, char **new_env)
{
	if (execve(cmd->arg_to_pass[0], cmd->arg_to_pass, new_env) == -1)
	{
		free_env_ms(ms->env.env_ms);
		ft_free_tab_char(new_env);
		if (errno == 13)
			fprintf(stderr, "minishell: %s: Is a directory\n",
				cmd->arg_to_pass[0]);
		else
			fprintf(stderr, "minishell: %s: command not found\n",
				cmd->arg_to_pass[0]);
		if (errno == 13)
			g_sig_error = 126;
		else
			g_sig_error = 127;
		free_list(ms->args);
		exit (g_sig_error);
	}
}

char	**get_new_env(t_env_ms *env_ms)
{
	t_it	it;
	char	**new;

	init_struct_it(&it);
	it.len = size_env(env_ms);
	new = malloc(sizeof(char *) * (it.len + 1));
	if (new == NULL)
		return (NULL);
	while (env_ms)
	{
		new[it.i] = ft_strdup(env_ms->var);
		it.i++;
		env_ms = env_ms->next;
	}
	new[it.i] = NULL;
	return (new);
}

int	other_executable(t_struct *ms, t_args *cmd)
{
	int			status;
	pid_t		pid;
	char		**new_env;

	status = 0;
	new_env = get_new_env(ms->env.env_ms);
	pid = fork();
	if (pid == -1)
	{
		g_sig_error = 127;
		return (g_sig_error);
	}
	signal(SIGINT, handle_signal_child);
	signal(SIGQUIT, handle_signal_child);
	if (pid > 0)
		handle_father(ms, status, pid);
	else
		handle_child(ms, cmd, new_env);
	ft_free_tab_char(new_env);
	return (0);
}
