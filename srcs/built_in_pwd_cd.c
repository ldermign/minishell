/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:19:57 by ldermign          #+#    #+#             */
/*   Updated: 2022/01/25 14:04:50 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_old_pwd(t_env_ms **stack, char *name, char *new_path)
{
	t_env_ms	*first;

	first = *stack;
	while (*stack && ft_pos_strstr((*stack)->var, name) == -1)
		*stack = (*stack)->next;
	if (*stack != NULL)
		free((*stack)->var);
	(*stack)->var = ft_alloc_strcat(name, new_path);
	*stack = first;

}

int	built_in_cd(t_env *env, char **cmd_args)
{
	char	*path_to_go;
	char	actual_path[PATH_MAX];

	if (search_for_var_in_env(&(env->env_ms), "OLDPWD") == -1)
		add_var_env_minishell(&(env->env_ms),
		ft_alloc_strcat("OLDPWD=", getcwd(actual_path, sizeof(actual_path))));
	else
		change_old_pwd(&(env->env_ms), "OLDPWD=", getcwd(actual_path, sizeof(actual_path)));
	path_to_go = ft_alloc_strcat("./", cmd_args[1]);
	if (chdir(path_to_go) == -1)
		perror("cd");
	getcwd(actual_path, sizeof(actual_path));
	env->abs = actual_path;
	change_old_pwd(&(env->env_ms), "PWD=", getcwd(actual_path, sizeof(actual_path)));
	free(path_to_go);
	return (1);
}

int	built_in_pwd()
{
	char	actual_path[PATH_MAX];

	if (getcwd(actual_path, sizeof(actual_path)) != NULL)
		printf("%s\n", actual_path);
	else
		perror("getcwd");
	return (1);
}
