/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:31:22 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/31 12:47:22 by ldermign         ###   ########.fr       */
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

int	execute_cmd_execve(t_struct *ms, t_execute *exec, char **cmd)
{
	ft_free_all(ms);
	if (exec->str_path == NULL
		|| execve(exec->str_path, cmd, exec->new_env) == -1)
	{
		if (errno == 13)
			fprintf(stderr, "minishell: %s: Is a directory\n", cmd[0]);
		else
			fprintf(stderr, "minishell: %s: command not found\n", cmd[0]);
		ft_free_struct_execute(exec);
		free_list(ms->args);
		if (ms->pipex != NULL)
			free(ms->pipex);
		if (errno == 13)
			g_sig_error = 126;
		else
			g_sig_error = 127;
		exit (g_sig_error);
	}
	return (0);
}

void	handle_father(t_struct *ms, int status, int pid)
{
	ms->pid = pid;
	if (waitpid(pid, &status, 0) == -1)
		perror("waitpid() failed\n");
	if (WIFEXITED(status))
		g_sig_error = WEXITSTATUS(status);
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
	{
		g_sig_error = 127;
		return (g_sig_error);
	}
	signal(SIGINT, handle_signal_child);
	signal(SIGQUIT, handle_signal_child);
	if (pid > 0)
		handle_father(ms, status, pid);
	else
		execute_cmd_execve(ms, &exec, stack->arg_to_pass);
	ft_free_struct_execute(&exec);
	return (0);
}
