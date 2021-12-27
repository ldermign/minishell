/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:36 by ldermign          #+#    #+#             */
/*   Updated: 2021/12/27 22:02:08 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var_envs(char **env, t_env *cpy_env)
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
		return (EXIT_FAILURE);
	}
	while (i < nbr_env)
	{
		cpy_env->env[i] = env[i];
		i++;
	}
	cpy_env->env[i] = NULL;
	// for (int j = 0 ; j < i ; j++)
	// 	printf("env[%d] = %s\n", j, cpy_env->env[j]);
	return (EXIT_SUCCESS);
}

void	quit_minishell(int sig)
{
	if (sig == SIGINT)
		exit(0); //revoir lol

}

int	main(int ac, char **av, char **env)
{
	(void)av;
	char	*line;
	t_env	cpy_env;

	line = NULL;
	if (ac != 1)
	{
		printf("Error, too many arguments.\n");
		return (0);
	}
	if (get_var_envs(env, &cpy_env) == EXIT_FAILURE)
		return (0);
	
	signal(SIGINT, quit_minishell);
	while (42)
	{
		line = readline("$ ");
		get_prompt(line);
	}
	return (0);
}