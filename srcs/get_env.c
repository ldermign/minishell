/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:35:14 by ldermign          #+#    #+#             */
/*   Updated: 2022/01/16 21:52:49 by ldermign         ###   ########.fr       */
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
	cpy_env->env = malloc(sizeof(char *) * nbr_env);
	if (cpy_env == NULL)
	{
		printf("Error malloc.\n");
		return ;
	}
	while (i < nbr_env)
	{
		cpy_env->env[i] = env[i];
		i++;
	}
	cpy_env->env[i] = NULL;
}

void	get_var_path(char **env, t_env *cpy_env)
{
	int	i;

	i = 0;
	while (env[i] && ft_pos_strstr(env[i], "PATH") == -1)
		i++;
	cpy_env->path = ft_split(&env[i][5], ':');
	// i = 0;
	// while (cpy_env->path[i])
	// {
	// 	printf(GREEN"path = [%s]\n"NORMAL, cpy_env->path[i]);
	// 	i++;
	// }
}

int	recup_var_envs(char **env, t_env *cpy_env)
{
	get_all_env(env, cpy_env);
	get_var_path(env, cpy_env);
	return (EXIT_SUCCESS);
}
