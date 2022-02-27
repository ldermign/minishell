/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:46:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/26 21:01:54 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_tab(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i])
		i++;
	return (i);
}

static int	size_str(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i + 1] && str[i] == ' ' && str[i + 1] == '-')
		{
			len++;
			i++;
		}
		if (str[i] != ' ')
			len++;
		i++;
	}
	return (len);
}

static char	*fill_in(char *to_fill, char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i + 1] && str[i] == ' ' && str[i + 1] == '-')
		{
			to_fill[j] = str[i];
			i++;
			j++;
		}
		if (str[i] != ' ')
		{
			to_fill[j] = str[i];
			j++;
		}
		i++;
	}
	to_fill[j] = '\0';
	return (to_fill);
}

char	**clean_args(char **cmd)
{
	int		i;
	int		size_tab;
	char	**new_tab;

	i = 0;
	size_tab = len_tab(cmd);
	new_tab = malloc(sizeof(char *) * size_tab + 1);
	if (new_tab == NULL)
		return (NULL);
	while (cmd[i])
	{
		new_tab[i] = malloc(sizeof(char) * size_str(cmd[i]) + 1);
		if (new_tab[i] == NULL)
			return (NULL);
		new_tab[i] = fill_in(new_tab[i], cmd[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

void	chaipa(t_struct *ms, char **env, char **cmd)
{
	int		status;
	int		pid;
	int		pipe_fd[2];

	status = 0;
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		sig_error = 127;
		perror("fork");
		return ;
	}
	// printf("pid = %d\n", pid);
	if (pid != 0)
	{
		close(pipe_fd[1]);
		// close(pipe_fd[0]);
		dup2(pipe_fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
		// kill(pid, SIGTERM);
	}
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		// execve(working_path(ms->env.path, cmd[0]), cmd, env) == -1
		if (execve(working_path(ms->env.path, cmd[0]), cmd, env) == -1)
		{
			printf("minishell: %s: command not found\n", cmd[0]);
			sig_error = 127;
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			close_all_fd(&(ms->std));
			return ;
		}
		// close(pipe_fd[0]);
		// close(pipe_fd[1]);
		if (pipe_fd[0] != 0)
			close(pipe_fd[0]);
		// printf("pipe_fd[0] = %d, pipe_fd[1] = %d\n", pipe_fd[0], pipe_fd[1]);
	}
	// close_all_fd(&(ms->std));
	sig_error = 0;
}

int	pass_previous_cmd(char **old_cmd)
{
	int	i;

	i = 0;
	while (old_cmd[i] && old_cmd[i][0] != '|')
		i++;
	if (old_cmd[i] && old_cmd[i][0] == '|')
		i++;
	return (i);
}

char	**get_good_args_for_cmd(char **cmd_pipe)
{
	int		i;
	int		j;
	char	**new;

	i = 0;//line
	j = 0;
	while (cmd_pipe[i] && cmd_pipe[i][0] != '|')
		i++;
	new = malloc(sizeof(char *) * i + 1);
	if (new == NULL)
		return (NULL);
	while (j < i)
	{
		new[j] = cmd_pipe[j];
		j++;
	}
	new[j] = NULL;
	return (new);
}

void	there_is_pipe(t_struct *ms, char *prompt)
{
	int		i;
	char	**cmd_pipe;
	char	**new_args;

	i = 0;
	cmd_pipe = get_cmd_and_args_split(&prompt[i]);
	int len = len_tab(cmd_pipe);
	while (i < len)
	{
		printf("Xavier a tort\n");
		new_args = get_good_args_for_cmd(&cmd_pipe[i]);
		printf("Xaviort\n");
		chaipa(ms, ms->env.env_bash, new_args);
		printf("Xa\n");
		i += pass_previous_cmd(&cmd_pipe[i]);
		printf("tort\n");
		ft_free_tab(new_args);
		
	}
	close_all_fd(&(ms->std));
}

/*

Commandes a tester =>

ls -l | wc -cl
ls | wc
ls | sort
cat /dev/urandom | head -c 1000 | wc -c

En trover d'autres...

*/

// tab[0] = ls
// tab[1] = -l

// // 2eme tour

// tab[0] = wc
// tab[1] =