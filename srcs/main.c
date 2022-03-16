/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/16 16:13:42 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_error = 0;

void	other_executable(t_struct *ms, t_args *cmd, char **env_bash)
{(void)env_bash;
	int		status;
	pid_t	pid;
	
	if (cmd->command[0] == '.' && cmd->command[1] && cmd->command[1] == '/')
	{
		status = 0;
		pid = fork();
		if (pid == -1)
		{
			g_sig_error = 127;
			perror("fork");
			return ;
		}
		signal(SIGINT, handle_signal_child);
		signal(SIGQUIT, handle_signal_child);
		if (pid > 0)
		{
			ms->pid = pid;
			waitpid(pid, &status, 0);
		}
		else
		{
			if (execve(cmd->command, cmd->arg_to_pass, NULL) == -1)
			{
				printf("minishell: %s: command not found\n", cmd->arg_to_pass[0]);
				g_sig_error = 127;
				// creer fonction qui close all
				// freeetoutbalalandls
				exit (127); // revoir l'exit
			}
		}
		g_sig_error = 0;
	}
}

void	command(t_struct *ms)
{
	int		i;
	int		last;
	t_args	*all_cmds;

	i = 0;
	all_cmds = ms->args->first;
	last = last_redir(all_cmds->redir);
	init_struct_std(all_cmds->redir, &(*ms).std, last);
	if (ms->parsing.nb_pipe > 0)
		there_is_pipe(ms);
	else if (last == -1 && built_in(ms, all_cmds) == -1)
		execute_cmd_with_fork(ms, all_cmds);
	else if (last != -1)
		redirection(ms, all_cmds, NULL);
	else
		other_executable(ms, all_cmds, ms->env.env_bash);
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
		exit(g_sig_error);
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
