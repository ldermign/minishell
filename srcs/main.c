/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/23 10:33:35 by ejahan           ###   ########.fr       */
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
	while (42)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, handle_signal);
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
	