/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/07 15:52:30 by ldermign         ###   ########.fr       */
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
	t_struct	structure;
	// t_env	cpy_env;
	// t_parsing	parsing;

	line = NULL;
	if (ac != 1)
	{
		printf("Error, too many arguments.\n");
		return (0);
	}
	if (recup_var_envs(env, &structure.env) == EXIT_FAILURE)
		return (0);

	// {
	// 	free_lst(cpy_env.env_ms);
	// 	// ft_free_tab(cmd_args);
	// 	ft_free_tab(cpy_env.path);
	// 	free(line);
	// 	exit (0);
	// }
	// char cmd[] = "echo \"test $PWD pouet\"";
	
	while (42)
	{
	// 	signal(SIGINT, line_break);
	// 	// signal(SIGQUIT, quit_minishell); // ctrl+'\'
	// 	// signal(0, test);
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