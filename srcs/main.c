/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/31 10:12:29 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_error = 0;

void	command(t_struct *ms)
{
	int		i;
	int		last;
	t_args	*all_cmds;

	i = 0;
	if (ms->args->first->arg_to_pass == NULL)
		return ;
	all_cmds = ms->args->first;
	last = max(last_left(all_cmds->command), last_right(all_cmds->command));
	init_struct_std(all_cmds, &(*ms).std, last);
	ms->pipex = NULL;
	if (ms->parsing.nb_pipe > 0)
	{
		// fprintf(stderr, "PIPE\n");
		there_is_pipe(ms);
	}
	else if (is_new_executable(all_cmds->command) != -1
		|| (check_if_variable_already_exist(ms->env.env_ms, "PATH=") == -1
			&& is_built_in(all_cmds->command) == -1))
	{
		// fprintf(stderr, "NOUVEL EXECUTABLE\n");
		other_executable(ms, all_cmds);
	}
	else if (last != -1 || ft_pos_strstr(all_cmds->command, "<<") != -1)
	{
		// fprintf(stderr, "REDIRECTIONS\n");
		redirection(ms, all_cmds, NULL);
	}
	else if (last == -1 && built_in(ms, all_cmds) == -1)
	{
		// fprintf(stderr, "PAS BUILT_IN, LS, MKDIR...\n");
		execute_cmd_with_fork(ms, all_cmds);
	}
}

void	loop(t_struct *minish)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	line = readline("$ ");
	if (line == NULL)
		ctrl_d_main(minish);
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
		// signal(SIGPIPE, SIG_IGN);
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		loop(&structure);
	}
	ft_free_all(&structure);
	return (0);
}
