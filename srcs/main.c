/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/13 21:28:37 by ldermign         ###   ########.fr       */
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

	// command("ls > pouet", &structure);
	// printf("[ls > pouet OK]\n");
	// command("cat pouet", &structure);
	// printf("[cat pouet OK]\n");
	// command("> pouet", &structure);
	// printf("[> pouet OK]\n");
	// command("cat pouet", &structure);
	// printf("[cat pouet OK]\n");

	// while (42)
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
	return (0);
}
