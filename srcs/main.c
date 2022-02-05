/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/05 17:02:28 by ldermign         ###   ########.fr       */
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



	// {
	// 	free_lst(cpy_env.env_ms);
	// 	// ft_free_tab(cmd_args);
	// 	ft_free_tab(cpy_env.path);
	// 	free(line);
	// 	exit (0);
	// }
	while (42)
	{
		signal(SIGINT, line_break); // PAS BONNNNN ctrl+c
		// signal(SIGQUIT, quit_minishell); // ctrl+'\'
		// signal(0, test);
		line = readline("$ ");
					// get_prompt(line, &cpy_env);
					init_parsing(&parsing);
					// parse_line(line, &parsing);
					if (parsing.result != NULL)
						free(parsing.result);
		if (line[0] != '\0')
			get_prompt(line, &cpy_env);
		free(line);
	}
	
	return (0);
}