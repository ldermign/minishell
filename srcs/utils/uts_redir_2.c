/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_redir_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:21:18 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/25 15:21:46 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pos_last_redir_right(char **args)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (args[i])
	{
		if (args[i][0] == '>')
		{
			if (args[i][1] == ' ')
				last = i;
			else if (args[i][1] && args[i][1] == '>' && args[i][2] == ' ')
				last = i;
		}
		i++;
	}
	return (last);
}

int	pos_last_redir_left(char **args)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (args[i])
	{
		if (args[i][0] == '<')
		{
			if (args[i][1] == ' ')
				last = i;
			else if (args[i][1] && args[i][1] == '<' && args[i][2] == ' ')
				last = i;
		}
		i++;
	}
	return (last);
}

char	*recup_name(char *args)
{
	char	*name;
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	j = 0;
	while (args[i] && args[i] != ' ')
		i++;
	i++;
	while (args[i + j])
		j++;
	name = malloc(sizeof(char) * j + 1);
	if (name == NULL)
		return (NULL);
	name[j] = '\0';
	while (k < j)
		name[k++] = args[i++];
	return (name);
}

/*

	int		ret;
	char	*path_to_go;
	char	*old_pwd;
	char	act_path[PATH_MAX];

	ret = check_if_variable_already_exist(env->env_ms, "OLDPWD=");
	old_pwd = ft_alloc_strcat("OLDPWD=", getcwd(act_path, sizeof(act_path)));
	if (ret == -1)
		add_var_env_minishell(&(env->env_ms), old_pwd);
	else
		change_old_pwd(&(env->env_ms), "OLDPWD=", old_pwd);
	path_to_go = ft_alloc_strcat("./", new_to_go);
	if (chdir(path_to_go) == -1)
		sig_error("cd", errno);
	free(path_to_go);
	path_to_go = ft_alloc_strcat("PWD=", getcwd(act_path, sizeof(act_path)));
	env->abs = act_path;
	change_var_env_minishell(env->env_ms, path_to_go,
		check_if_variable_already_exist(env->env_ms, "PWD="));
	return (1);

*/