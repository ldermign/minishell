/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd_cd_echo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:19:57 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/29 13:01:08 by ldermign         ###   ########.fr       */
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

static void	go_to_home(t_env *env)
{
	int		pos;
	char	*home;

	pos = check_if_variable_already_exist(env->env_ms, "HOME=");
	if (pos == -1)
		return ;
	home = get_variable_with_pos(env->env_ms, pos);
	if (chdir(&home[5]) == -1)
	{
		g_sig_error = 127;	//	non, revoir
	}
}

int	built_in_cd(t_env *env, char *new_to_go)
{
	int		ret;
	char	*path_to_go;
	char	*old_pwd;
	char	act_path[PATH_MAX];

	if (new_to_go == NULL)
	{
		go_to_home(env);
		return (1);
	}
	ret = check_if_variable_already_exist(env->env_ms, "OLDPWD=");
	old_pwd = ft_strjoin("OLDPWD=", getcwd(act_path, sizeof(act_path)));
	if (ret == -1)
		add_var_env_minishell(&(env->env_ms), old_pwd);
	else
		change_old_pwd(&(env->env_ms), "OLDPWD=", old_pwd);
	path_to_go = ft_strjoin("./", new_to_go); 
	if (chdir(path_to_go) == -1)
	{
		fprintf(stderr, "minishell: cd: %s: No such file or directory\n", new_to_go);
		g_sig_error = 1;
	}
	else
		g_sig_error = 0;
	free(path_to_go);
	path_to_go = ft_strjoin("PWD=", getcwd(act_path, sizeof(act_path)));
	change_var_env_minishell(env->env_ms, path_to_go,
		check_if_variable_already_exist(env->env_ms, "PWD="));
	return (g_sig_error);
}

int	built_in_pwd()
{
	char	actual_path[PATH_MAX];

	if (getcwd(actual_path, sizeof(actual_path)) != NULL)
	{
		write(1, actual_path, ft_strlen(actual_path));
		write(1, "\n", 1);
		g_sig_error = 0;
	}
	else
		g_sig_error = 127;
	return (g_sig_error);
}

int	built_in_echo(t_struct *ms)
{
	char	*sig;
	int		len;

	sig = 0;
	len = ft_strlen(ms->parsing.result);
	if (write(1, ms->parsing.result, len) == -1)
	{
		free(ms->parsing.result);
		fprintf(stderr, "echo: write error: No space left on device\n"); // ca marche pas du tout
		return (EXIT_FAILURE);
	}
	if (ms->parsing.option != 1)
		write(1, "\n", 1);
	free(ms->parsing.result);
	g_sig_error = 0;
	//	checker si pas echo $?
	return (g_sig_error);
}
