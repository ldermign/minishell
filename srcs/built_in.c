/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:19:48 by ldermign          #+#    #+#             */
/*   Updated: 2022/01/19 23:22:03 by ldermign         ###   ########.fr       */
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

int	built_in_cd(t_env *env, char **cmd_args)
{
	char	*path_to_go;
	char	actual_path[PATH_MAX];

	path_to_go = ft_alloc_strcat("./", cmd_args[1]);
	if (chdir(path_to_go) == -1)
		perror("cd");
	getcwd(actual_path, sizeof(actual_path));
	env->abs = actual_path;
	free(path_to_go);
	return (1);
}

int	built_in_pwd(t_env *env, char **cmd_args)
{
	(void)env;
	(void)cmd_args;
	char	actual_path[PATH_MAX];

	if (getcwd(actual_path, sizeof(actual_path)) != NULL)
		printf("%s\n", actual_path);
	else
		perror("getcwd");
	return (1);
}

int	built_in_to_create(t_env *env, char **cmd_args)
{
	(void)env;
	if (ft_pos_strstr(cmd_args[0], "cd") != -1)
		return (built_in_cd(env, cmd_args));
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
	// print_tab_char(args);
	if (built_in_to_create(env, args) == 1)
	{
		ft_free_tab(args);
		return ;
	}
	good_path = working_path(env->path, args[0]);
	execute_cmd(good_path, args, env->env);
	// err = execve(good_path, args, env->env);
	// if (err == -1)
	// printf("err = %d\n", err);
	ft_free_tab(args);
}
