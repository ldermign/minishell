/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:36 by ldermign          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/02/10 20:05:17 by ejahan           ###   ########.fr       */
=======
/*   Updated: 2022/02/11 15:57:25 by ldermign         ###   ########.fr       */
>>>>>>> liena
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_minishell(int sig)
{
	// free les structures 
	if (sig == SIGQUIT)
	{
		write(1, "exit\n", 6);
		exit(0);
	}
}

void	line_break(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		// rl_replace_line("\n", 0);
	}
	// printf("la \n");
	return ;
}

void	test(int sig)
{
	if (sig == 0)
		printf("test\n");
}

void	init_parsing(t_parsing *parsing)
{	
	parsing->error = 0;
	parsing->result = NULL;
	parsing->file_redirection = NULL;
	parsing->i_line = 0;
	parsing->option = 0;
	parsing->red1 = 0;
	parsing->red2 = 0;
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_struct	structure;

	(void)av;
	line = NULL;
	if (ac != 1)
	{
		printf("Error, too many arguments.\n");
		return (0);
	}
	if (recup_var_envs(env, &structure.env) == EXIT_FAILURE)
		return (0);
<<<<<<< HEAD
=======

	command("ls ~/ > la", &structure)

	// while (42)
>>>>>>> liena
	// {
	// 	// signal(SIGINT, line_break);
	// 	// signal(SIGQUIT, quit_minishell); // ctrl+'\'
	// 	// signal(0, test);
	// 	line = readline("$ ");
	// 	init_parsing(&structure.parsing);
	// 	parse_line(line, &structure.parsing);
	// 	if (line[0] != '\0' && structure.parsing.error != 1)
	// 		command(line, &structure);
	// 	if (structure.parsing.result != NULL)
	// 		free(structure.parsing.result);
	// 	free(line);
	// }
<<<<<<< HEAD
	// char cmd[] = "echo \"test $PWD pouet\"";
	while (42)
	{
	// 	signal(SIGINT, line_break);
	// 	signal(SIGQUIT, quit_minishell); // ctrl+'\'
	// 	signal(0, test);
		line = readline("$ ");
		init_parsing(&structure.parsing);
		parse_line(line, &structure.parsing);
		if (line[0] != '\0' && structure.parsing.error != 1)
			command(line, &structure);
		if (structure.parsing.result != NULL)
			free(structure.parsing.result);
		free(line);
	}
	// command(cmd, &structure);
=======
>>>>>>> liena
	return (0);
}
