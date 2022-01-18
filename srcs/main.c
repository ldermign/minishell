/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/01/17 14:51:24 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_minishell(int sig)
{
	// free les structures 
	if (sig == SIGINT)
	{
		printf(RED"EXIT par la fonction du minishell.\n"NORMAL);
		exit(0);
	}
}

int	get_prompt(char *prompt, t_env *env)
{
	start_built_in(prompt, env);
	return (0);
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
	if (recup_var_envs(env, &cpy_env) == EXIT_FAILURE)
		return (0);
	// get_prompt("ls -a -l", &cpy_env);
	// get_prompt("mkdir test", &cpy_env);
	signal(SIGINT, quit_minishell);
	while (42)
	{
		line = readline("$ ");
		get_prompt(line, &cpy_env);
		free(line);
	}
	return (0);
}