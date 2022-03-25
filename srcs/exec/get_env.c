/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:35:14 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/25 10:42:43 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pos_var(char **env, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i][j])
	{
		while (str[j] && env[i][j] && str[j] == env[i][j])
			j++;
		if (str[j] == '\0')
			break ;
		else
			j = 0;
		i++;
	}
	return (i);
}

char	*get_pwd_and_path(char **env, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		while (str[j])
		{
			while (env[i][j] == str[j])
				j++;
			if (str[j] == '\0')
				return (&env[i][ft_strlen(str)]);
			else
			{
				j = 0;
				break ;
			}
		}
		i++;
	}
	return (NULL);
}

int	recup_var_envs(char **env, t_env *cpy_env)
{
	int	i;

	cpy_env->env_ms = NULL;
	i = 0;
	while (env[i])
	{
		add_var_env_minishell(&(cpy_env->env_ms), env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
