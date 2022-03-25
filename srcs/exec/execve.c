/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:31:22 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/25 09:16:31 by ldermign         ###   ########.fr       */
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

char	*working_path(char **paths, char *name_fct)
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
		new[it.i] = ft_strdup(env_ms->var);
		it.i++;
		env_ms = env_ms->next;
	}
	new[it.i] = NULL;
	return (new);
}

int	execute_cmd_execve(t_struct *ms, t_execute *exec, char **cmd)
{
	// print_tab_char(exec->new_env);
	// print_tab_char(exec->paths);
	// printf("%s\n", exec->str_path);	// il est a null
	if (exec->str_path == NULL || execve(exec->str_path, cmd, exec->new_env) == -1)
	{
		printf("minishell: %s: command not found\n", cmd[0]);
		ft_free_struct_execute(exec);
		free_list(ms->args);
		// free_env_ms(ms->env.env_ms);
		if (ms->parsing.nb_pipe > 0)
			free(ms->pipex);
		exit (sig_error(NULL, 127));
	}
	// sig_error(NULL, 0);
	// ft_free_tab_char(new_env);
	// ft_free_tab_char(paths);
	// free(str_path);
	return (0);
}

int	execute_cmd_with_fork(t_struct *ms, t_args *stack)
{
	int			status;
	pid_t		pid;
	t_execute	exec;

	status = 0;
	init_struct_execute(ms, &exec, stack->arg_to_pass);
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
	{
		ft_free_all(ms);
		execute_cmd_execve(ms, &exec, stack->arg_to_pass);
	}
	ft_free_struct_execute(&exec);
	return (0);
}
