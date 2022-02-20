/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd_cd_echo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:19:57 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/20 19:05:50 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_old_pwd(t_env_ms **stack, char *name, char *str)
{
	t_env_ms	*first;

	first = *stack;
	while (*stack && ft_pos_strstr((*stack)->var, name) == -1)
		*stack = (*stack)->next;
	(*stack)->var = str;
	*stack = first;

}

int	built_in_cd(t_env *env, char **cmd_args)
{
	int		ret;
	char	*path_to_go;
	char	*old_pwd;
	char	actual_path[PATH_MAX];

	ret = check_if_variable_already_exist(&(env->env_ms), "OLDPWD=");
	old_pwd = ft_alloc_strcat("OLDPWD=", getcwd(actual_path, sizeof(actual_path)));
	if (ret == -1)
		add_var_env_minishell(&(env->env_ms), old_pwd);
	else
		change_old_pwd(&(env->env_ms), "OLDPWD=", old_pwd);
	path_to_go = ft_alloc_strcat("./", cmd_args[1]);
	if (chdir(path_to_go) == -1)
	{
		sig_error = errno;
		perror("cd");
	}
	free(path_to_go);
	path_to_go = ft_alloc_strcat("PWD=", getcwd(actual_path, sizeof(actual_path)));
	env->abs = actual_path;
	change_var_env_minishell(&(env->env_ms), path_to_go, check_if_variable_already_exist(&(env->env_ms), "PWD="));
	return (1);
}

int	built_in_pwd()
{
	char	actual_path[PATH_MAX];

	if (getcwd(actual_path, sizeof(actual_path)) != NULL)
		printf("%s\n", actual_path);
	else
	{
		sig_error = errno;
		perror("getcwd");
	}
	return (1);
}

int	built_in_echo(t_struct *ms, char **args, char *prompt)
{
	int		i;
	int		len;
	int		line_break;

	i = 0;
	line_break = light_parse_echo(prompt);
	if (args[0] && args[1] && ft_pos_strstr(args[1], "$?") != -1)
	{
		printf("%d\n", sig_error);
		return (EXIT_SUCCESS);
	}
	if (line_break != -1)
		i = line_break;
	else
	{
		while (prompt[i] == ' ')
			i++;
		i += 4;
		while (prompt[i] == ' ')
			i++;
	}
	len = ft_strlen(ms->parsing.result);
	write(ms->std.fd_to_write, ms->parsing.result, len);
	if (line_break == -1) //gerer cas ou $$ chaipukoi
		write(ms->std.fd_to_write, "\n", 1);
	return (EXIT_SUCCESS);
}
