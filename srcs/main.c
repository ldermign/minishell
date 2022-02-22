/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/22 23:56:22 by ejahan           ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	char		*line;
	int			i;
	t_struct	structure;

	(void)av;
	line = NULL;
	i = 0;
	if (ac != 1)
	{
		printf("Error, too many arguments.\n");
		return (0);
	}
	if (recup_var_envs(env, &structure.env) == EXIT_FAILURE)
		return (0);

	// command("ls ~/ > la", &structure)

	// while (42)./
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
		while (line[i] == ' ')
			i++;
		if (line[i] != '\0')
			parsing(line, &structure);
		// printf("recup echo parsing : [%s]\n", structure.parsing.result);
		i = 0;
		// if (line[0] != '\0' && structure.parsing.error != 1)
		// 	command(line, &structure);
		// if (structure.parsing.result != NULL)
		// 	free(structure.parsing.result);
		free(line);
	}
	// command(cmd, &structure);
	return (0);
}

// minish->parsing.result = recup_echo(minish->args->first->arg_to_pass, minish);
	