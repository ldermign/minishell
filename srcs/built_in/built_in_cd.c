/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:39:46 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/31 11:02:30 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_old_pwd(t_env_ms **stack, char *name, char *str)
{
	t_env_ms	*first;

	first = *stack;
	while (*stack && ft_pos_strstr((*stack)->var, name) == -1)
		*stack = (*stack)->next;
	free((*stack)->var);
	(*stack)->var = ft_strdup(str);
	*stack = first;
}

static int	go_to_home(t_env *env)
{
	int		pos;
	char	*home;

	pos = check_if_variable_exist(env->env_ms, "HOME=");
	if (pos == -1)
		return (0);
	home = get_var_with_pos(env->env_ms, pos);
	if (chdir(&home[5]) == -1)
		g_sig_error = 127;
	else
		g_sig_error = 1;
	return (g_sig_error);
}

static int	error_path_null(char *old_pwd, char *path)
{
	if (old_pwd != NULL)
		free(old_pwd);
	fprintf(stderr, "minishell: cd: %s: No such file or directory\n", path);
	free(path);
	g_sig_error = 1;
	return (g_sig_error);
}

int	built_in_cd(t_env *env, char *new_to_go)
{
	int		ret;
	char	*path_to_go;
	char	*old_pwd;
	char	act_path[PATH_MAX];

	if (new_to_go == NULL)
		return (go_to_home(env));
	ret = check_if_variable_exist(env->env_ms, "OLDPWD=");
	old_pwd = ft_strjoin("OLDPWD=", getcwd(act_path, sizeof(act_path)));
	path_to_go = ft_strjoin("./", new_to_go);
	if (old_pwd == NULL || chdir(path_to_go) == -1)
		return (error_path_null(old_pwd, path_to_go));
	else
		g_sig_error = 0;
	if (ret == -1)
		add_var_env_minishell(&(env->env_ms), old_pwd);
	else
		change_old_pwd(&(env->env_ms), "OLDPWD=", old_pwd);
	free(old_pwd);
	free(path_to_go);
	path_to_go = ft_strjoin("PWD=", getcwd(act_path, sizeof(act_path)));
	change_var_env_minishell(env->env_ms, path_to_go,
		check_if_variable_exist(env->env_ms, "PWD="));
	free(path_to_go);
	return (g_sig_error);
}
