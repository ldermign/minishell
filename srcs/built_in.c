/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:19:48 by ldermign          #+#    #+#             */
/*   Updated: 2022/01/25 14:39:40 by ldermign         ###   ########.fr       */
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

void	execute_cmd(char *path, char **args, char **env)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == -1)
		perror("Fork"); // voir le cas d'erreur
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(path, args, env) == -1)
			perror(args[0]); // voir le cas d'erreur
		exit(EXIT_FAILURE);
	}
}

int	built_in_env(t_env_ms *stack)
{
	while (stack)
	{
		printf("%s\n", stack->var);
		stack = stack->next;
	}
	return (EXIT_SUCCESS);
}

int	built_in_to_create(t_env *env, char **cmd_args)
{
	if (ft_pos_strstr(cmd_args[0], "cd") != -1)
		return (built_in_cd(env, cmd_args));
	else if (ft_pos_strstr(cmd_args[0], "pwd") != -1)
		return (built_in_pwd());
	else if (ft_pos_strstr(cmd_args[0], "env") != -1)
		return (built_in_env(env->env_ms));
	// else if (/* condition */)
	// {
	// 	/* code */
	// }
	return (-1);
}

void start_built_in(char *prompt, t_env *env)
{
	int		i;
	char	*good_path;
	char	**args;

	i = 0;
	args = get_cmd_and_args_split(prompt);
	if (built_in_to_create(env, args) != -1)
	{
		ft_free_tab(args);
		// print_env_ms(&(env->env_ms));
		return ;
	}
	good_path = working_path(env->path, args[0]);
	execute_cmd(good_path, args, env->env_bash);
	// err = execve(good_path, args, env->env);
	// if (err == -1)
	// printf("err = %d\n", err);
	ft_free_tab(args);
	// print_env_ms(&(env->env_ms));
}
