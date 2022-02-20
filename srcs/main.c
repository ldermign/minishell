/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/20 18:34:44 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig_error = 0;

void	handle_signal(int sig)
{
	if (sig == SIGQUIT)
	{
		sig_error = 0;
		write(2, "exit\n", 5);
		exit (0);
	}
	else if	(sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		sig_error = 130;
	}
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
	while (42)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, handle_signal);
		line = readline("$ ");
		init_parsing(&structure.parsing);
		if (parse_line(line, &structure.parsing) != -1)
		{
			command(line, &structure);
			if (structure.parsing.result != NULL)
				free(structure.parsing.result);
		}
		free(line);
	}
	return (0);
}
