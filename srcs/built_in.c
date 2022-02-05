/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:19:48 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/04 14:22:41 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	built_in_export(t_env *env, char *prompt)
{
	int		i;
	int		ret;
	char	*str;

	i = 6;
	if (light_parse_export(prompt) == -1)
	{
		printf("Error command export\n");
		return (EXIT_FAILURE);
	}
	while (prompt[i] == ' ')
		i++;
	str = get_good_variable(prompt);
	ret = check_if_variable_already_exist(&(env->env_ms), &prompt[i]);
	if (ret == -1)
		add_var_env_minishell(&(env->env_ms), str);
	else
		change_var_env_minishell(&(env->env_ms), str, ret);
	// print_env_ms(&(env->env_ms));
	return (EXIT_SUCCESS);
}

int	built_in_to_create(t_env *env, char **cmd_args, char *prompt)
{
	// print_tab_char(cmd_args);
	if (ft_pos_strstr(cmd_args[0], "cd") != -1)
		return (built_in_cd(env, cmd_args));
	else if (ft_pos_strstr(cmd_args[0], "pwd") != -1)
		return (built_in_pwd());
	else if (ft_pos_strstr(cmd_args[0], "env") != -1)
		return (built_in_env(env->env_ms));
	else if (ft_pos_strstr(cmd_args[0], "export") != -1)
		return (built_in_export(env, prompt));
	else if (ft_pos_strstr(cmd_args[0], "unset") != -1)
		return (built_in_unset(env, cmd_args));
	else if (ft_pos_strstr(cmd_args[0], "echo") != -1)
		return (built_in_echo(prompt));
	else if (ft_pos_strstr(cmd_args[0], "exit") != -1)
		built_in_exit(env, cmd_args, prompt);
	return (-1);
}

void start_built_in(char *prompt, t_env *env)
{
	int		i;
	char	*good_path;
	char	**args;

	i = 0;
	while (prompt[i] == ' ')
		i++;
	args = get_cmd_and_args_split(&prompt[i]);
	if (built_in_to_create(env, args, prompt) != -1)
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
