/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/02 19:57:11 by ejahan           ###   ########.fr       */
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
	if (ac != 1)
	{
		printf("Error, too many arguments.\n");
		return (0);
	}
	if (recup_var_envs(env, &structure.env) == EXIT_FAILURE)
		return (0);
	while (42)
	{
		i = 0;
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, handle_signal);
		line = readline("$ ");
		// write(1, line, ft_strlen(line));
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i])
			parsing(&line[i], &structure);
		if (line[i] && structure.parsing.error != 1)
		{
			command(line, &structure);
			free_list(structure.args);
		}
		free(line);
	}
	// command(cmd, &structure);
	return (0);
}

// structure->args->first->arg_to_pass
// structure->args->first.command

// minish->parsing.result = recup_echo(minish->args->first->arg_to_pass, minish);
