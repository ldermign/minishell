/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/04 08:26:23 by ldermign         ###   ########.fr       */
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
	parsing->option = 0;
	parsing->red1 = 0;
	parsing->red2 = 0;
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
	// get_prompt("cd srcs", &cpy_env);
	// get_prompt("cd ..", &cpy_env);
	// get_prompt("export test=\"pouet pouet pouet la la la\" nonnisnka dnejkf", &cpy_env);
	// get_prompt("export test=bah oui mais non", &cpy_env);
	// get_prompt("export TEST=\"echo pouet\" non", &cpy_env);
	// get_prompt("unset test", &cpy_env);


	// get_prompt("   echo -n test non", &cpy_env);
	// get_prompt("echo -n-n--n test non", &cpy_env);
	// get_prompt("       echo -nnnnnn test non", &cpy_env);
	// get_prompt("echo -n -nnn -n -nn -n -n test non", &cpy_env);
	// get_prompt("echo test non", &cpy_env);
	// get_prompt("              echo test non", &cpy_env);
	// get_prompt("echo -------n pouet", &cpy_env);


	signal(SIGINT, quit_minishell);
	while (42)
	{
		line = readline("$ ");
					// get_prompt(line, &cpy_env);
					init_parsing(&parsing);
					parse_line(line, &parsing);
					if (parsing.result != NULL)
						free(parsing.result);
		get_prompt(line, &cpy_env);
		free(line);
	}
	
	return (0);
}