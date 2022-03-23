/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:35:14 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/23 14:37:52 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_all_env(char **env, t_env *cpy_env)
{
	int	i;
	int	nbr_env;

	i = 0;
	nbr_env = 0;
	while (env[nbr_env])
		nbr_env++;
	cpy_env->env_bash = malloc(sizeof(char *) * (nbr_env + 1));
	if (cpy_env->env_bash == NULL)
	{
		printf("Error malloc.\n");
		return ;
	}
	while (i < nbr_env)
	{
		cpy_env->env_bash[i] = env[i];
		i++;
	}
	cpy_env->env_bash[i] = NULL;
}

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

	cpy_env->env_bash = NULL;
	cpy_env->env_ms = NULL;
	get_all_env(env, cpy_env);
	i = 0;
	while (env[i])
	{
		add_var_env_minishell(&(cpy_env->env_ms), env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
