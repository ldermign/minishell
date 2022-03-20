/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/20 15:46:09 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command(t_struct *ms)
{
	int		i;
	int		last;
	t_args	*all_cmds;

	i = 0;
	if (ms->args->first->arg_to_pass == NULL)
		return ;
	all_cmds = ms->args->first;
	print_stack_cmd(all_cmds);
	last = last_redir(all_cmds->redir);
	init_struct_std(all_cmds->redir, &(*ms).std, last);
	if (ms->parsing.nb_pipe > 0)
		there_is_pipe(ms);
	else if (is_new_executable(all_cmds->command) == EXIT_SUCCESS)
		other_executable(ms, all_cmds, ms->env.env_bash);
	else if (last != -1)
		redirection(ms, all_cmds, NULL);
	else if (last == -1 && built_in(ms, all_cmds) == -1)
		execute_cmd_with_fork(ms, all_cmds);
}

void	loop(t_struct *minish)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	line = readline("$ ");
	if (line == NULL)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "exit\n", 5);
		exit(sig_error(NULL, 0));
	}
	if (line[i] != '\0')
		add_history(line);
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i])
		parsing(&line[i], minish);
	if (line[i] && minish->parsing.error == 0)
	{
		command(minish);
		if (minish->args != NULL)
			free_list(minish->args);
	}
	free(line);
}

int	main(int ac, char **av, char **env)
{
	t_struct	structure;

	(void)av;
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
		signal(SIGQUIT, SIG_IGN);
		loop(&structure);
	}
	return (0);
}
