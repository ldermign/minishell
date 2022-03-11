/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd_cd_echo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:19:57 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/11 15:20:53 by ldermign         ###   ########.fr       */
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

int	built_in_cd(t_env *env, char *new_to_go)
{
	int		ret;
	char	*path_to_go;
	char	*old_pwd;
	char	act_path[PATH_MAX];

	ret = check_if_variable_already_exist(&(env->env_ms), "OLDPWD=");
	old_pwd = ft_alloc_strcat("OLDPWD=", getcwd(act_path, sizeof(act_path)));
	if (ret == -1)
		add_var_env_minishell(&(env->env_ms), old_pwd);
	else
		change_old_pwd(&(env->env_ms), "OLDPWD=", old_pwd);
	path_to_go = ft_alloc_strcat("./", new_to_go);
	if (chdir(path_to_go) == -1)
	{
		g_sig_error = errno;
		perror("cd");
	}
	free(path_to_go);
	path_to_go = ft_alloc_strcat("PWD=", getcwd(act_path, sizeof(act_path)));
	env->abs = act_path;
	change_var_env_minishell(&(env->env_ms), path_to_go,
		check_if_variable_already_exist(&(env->env_ms), "PWD="));
	return (1);
}

int	built_in_pwd(void)
{
	char	actual_path[PATH_MAX];

	if (getcwd(actual_path, sizeof(actual_path)) != NULL)
		printf("%s\n", actual_path);
	else
	{
		g_sig_error = errno;
		perror("getcwd");
	}
	return (1);
}

int	built_in_echo(t_struct *ms)
{
	int		len;

	len = ft_strlen(ms->parsing.result);
	write(ms->std.fd_to_write, ms->parsing.result, len);
	//gerer cas ou $$ chaipukoi
	if (ms->parsing.option != 1)
		write(ms->std.fd_to_write, "\n", 1);
	free(ms->parsing.result);
	g_sig_error = 0;
	return (EXIT_SUCCESS);
}
