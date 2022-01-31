/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:35:14 by ldermign          #+#    #+#             */
/*   Updated: 2022/01/25 13:11:50 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_all_env(char **env, t_env *cpy_env)
{
	int	i;
	int	nbr_env;

	i = 0;
	nbr_env = 0;
	while (env[nbr_env] != NULL)
		nbr_env++;
	cpy_env->env_bash = malloc(sizeof(char *) * nbr_env);
	if (cpy_env == NULL)
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

int	pos_var(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i] && ft_pos_strstr(env[i], var) == -1)
		i++;
	return (i);
}

char	*get_absolute_path_beginning(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_pos_strstr(env[i], "PWD") == -1)
			i++;
		else
			return (&env[i][4]);
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
	cpy_env->path = ft_split(&env[pos_var(env, "PATH")][5], ':');
	cpy_env->abs = get_absolute_path_beginning(env);
	create_env_minishell(&(cpy_env->env_ms), env);
	print_env_ms(&(cpy_env->env_ms));
	return (EXIT_SUCCESS);
}
