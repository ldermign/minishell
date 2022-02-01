/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:35:14 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/01 14:25:28 by ldermign         ###   ########.fr       */
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

void	create_env_minishell(t_env_ms **env_minishell, char **env_bash)
{
	int	pos;

	pos = pos_var(env_bash, "PATH");
	add_var_env_minishell(env_minishell, env_bash[pos]);
	pos = pos_var(env_bash, "HOME");
	add_var_env_minishell(env_minishell, env_bash[pos]);
	pos = pos_var(env_bash, "PWD");
	add_var_env_minishell(env_minishell,
		ft_alloc_strcat("PWD=", &env_bash[pos][4]));
}

int	recup_var_envs(char **env, t_env *cpy_env)
{
	cpy_env->env_bash = NULL;
	cpy_env->path = NULL;
	cpy_env->abs = NULL;
	cpy_env->rel = NULL;
	cpy_env->env_ms = NULL;
	get_all_env(env, cpy_env);
	cpy_env->path = ft_split(get_pwd_and_path(env, "PATH="), ':');
	cpy_env->abs = get_pwd_and_path(env, "PWD=");
	create_env_minishell(&(cpy_env->env_ms), env);
	print_env_ms(&(cpy_env->env_ms));
	return (EXIT_SUCCESS);
}
