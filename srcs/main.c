/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/01/31 22:37:31 by elisa            ###   ########.fr       */
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

void	init_parsing(t_parsing *parsing)
{	
	parsing->error = 0;
	parsing->result = NULL;
	parsing->fd = NULL;
	parsing->i_line = 0;
	// parsing->echo = 0;
	// parsing->cd = 0;
	// parsing->pwd = 0;
	// parsing->export = 0;
	// parsing->unset = 0;
	// parsing->env = 0;
	// parsing->exit = 0;
	// parsing->simple_quotes = 0;
	// parsing->double_quotes = 0;
	parsing->option = 0;
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	char	*line;
	t_env	cpy_env;
	t_parsing	parsing;

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
		// get_prompt(line, &cpy_env);
		// init_parsing(&parsing);
		// parse_line(line, &parsing);
		// if (parsing.result != NULL)
		// 	free(parsing.result);
		get_prompt(line, &cpy_env);
		free(line);
	}
	return (0);
}