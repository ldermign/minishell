/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:31:22 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/21 15:36:19 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_path(char *path, char *cmd)
{
	size_t	i;
	int		j;
	char	*dst;

	if (path == NULL || cmd == NULL)
		return (NULL);
	i = 0;
	j = 0;
	dst = malloc(sizeof(char) * ft_strlen(path) + ft_strlen(cmd) + 2);
	if (dst == NULL)
		return (NULL);
	while (i < ft_strlen(path))
	{
		dst[i] = path[i];
		i++;
	}
	dst[i++] = '/';
	while (i < ft_strlen(path) + ft_strlen(cmd) + 1)
	{
		dst[i] = cmd[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*working_path(char **paths, char *name_fct)
{
	int		i;
	int		fd;
	char	*good_path;

	i = 0;
	if (paths == NULL)
		return (NULL);
	while (paths[i])
	{
		good_path = create_path(paths[i], name_fct);
		fd = access(good_path, F_OK & X_OK);
		if (fd == -1)
			i++;
		else
			return (good_path);
		free(good_path);
	}
	return (NULL);
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
		new[it.i] = malloc(sizeof(char) * (ft_strlen(env_ms->var) + 1));
		if (new[it.i] == NULL)
			return (NULL);
		new[it.i] = ft_strdup(env_ms->var);
		it.i++;
		env_ms = env_ms->next;
	}
	new[it.i] = NULL;
	return (new);
}

int	execute_cmd_execve(t_struct *ms, char **cmd)
{
	char	**new_env;
	char	**paths;
	char	*str_path;

	new_env = get_new_env(ms->env.env_ms);
	paths = ft_split(get_pwd_and_path(new_env, "PATH="), ':');
	str_path = working_path(paths, cmd[0]);
	if (execve(str_path, cmd, new_env) == -1)
	{
		printf("minishell: %s: command not found\n", cmd[0]);
		//	free new_env
		ft_free_tab_char(new_env);
		ft_free_tab_char(paths);
		free_list(ms->args);
		free(str_path);
		return (sig_error(NULL, 127));
	}
	sig_error(NULL, 0);
	ft_free_tab_char(new_env);
	ft_free_tab_char(paths);
	free(str_path);
	return (0);
}

int	execute_cmd_with_fork(t_struct *ms, t_args *stack)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (sig_error("fork", 127));
	signal(SIGINT, handle_signal_child);
	signal(SIGQUIT, handle_signal_child);
	if (pid > 0)
	{
		ms->pid = pid;
		waitpid(pid, &status, 0);
	}
	else
		exit (execute_cmd_execve(ms, stack->arg_to_pass));
	return (0);
}
