/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:46:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/07 16:06:55 by ldermign         ###   ########.fr       */
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

int	pass_previous_cmd(char **old_cmd, t_struct *ms)
{
	int	i;

	i = 0;
	while (old_cmd[i] && old_cmd[i][0] != '|')
		i++;
	if (old_cmd[i] && old_cmd[i][0] == '|')
	{
		ms->pipe_left = 1;
		i++;
	}
	else
		ms->pipe_left = 0;
	return (i);
}

char	**get_good_args_for_cmd(t_struct *ms, char **cmd_pipe)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	while (cmd_pipe[i] && cmd_pipe[i][0] != '|')
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (new == NULL)
		return (NULL);
	while (j < i)
	{
		new[j] = cmd_pipe[j];
		j++;
	}
	new[j] = (char *)NULL;
	if (cmd_pipe[j] && cmd_pipe[j][0] == '|')
		ms->pipe_right = 1;
	else
		ms->pipe_right = 0;
	return (new);
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

int	init_pipe(int fd[2][2])
{
	if (pipe(fd[0]) == -1 || pipe(fd[1]) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (1);
}

int	init_fork(int *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		g_sig_error = 127;
		perror("fork");
		return (-1);
	}
	return (1);
}

void	pipe_left_right(t_pipe *pipex)
{
	pipex->pipe_left = 0;
	pipex->pipe_right = 0;
	if (pipex->cmd_nbr != pipex->pipe_tot)
		pipex->pipe_right = 1;
	if (pipex->cmd_nbr != 0)
		pipex->pipe_left = 1;
	fprintf(stderr, "For [%d], left->[%d] & right->[%d] in total of [%d]\n", pipex->cmd_nbr, pipex->pipe_left, pipex->pipe_right, pipex->pipe_tot);
}

void	child_process(t_struct *ms, t_pipe *pipex, char **cmd, int test[ms->parsing.nb_pipe][2])
{
	int	i;

	i = 0;
	while (i < pipex->pipe - 1)
	{
		close(test[i][0]);
		close(test[i][1]);
		i++;
	}
	if (pipex->pipe_left == 1)
	{
		close(test[pipex->pipe - 1][1]);
		dup2(test[pipex->pipe - 1][0], STDIN_FILENO);
		close(test[pipex->pipe - 1][0]);
	}
	if (pipex->pipe_right == 1)
	{
		if (pipex->pipe != 0 && pipex->pipe_left == 0)
		{
			close(test[i][0]); // sur pipe - 1
			close(test[i][1]);
			i++; // sur pipe
		}
		close(test[pipex->pipe][0]);
		dup2(test[pipex->pipe][1], STDOUT_FILENO);
		close(test[pipex->pipe][1]);
		i++;
		while (i < pipex->pipe_tot)
		{
			close(test[i][0]);
			close(test[i][1]);
			i++;
		}
	}
	if (execve(working_path(ms->env.path, cmd[0]), cmd, ms->env.env_bash) == -1)
	{
		printf("minishell: %s: command not found\n", cmd[0]);
		g_sig_error = 127;
		close(pipex->fd1[0]);
		close(pipex->fd1[1]);
		close(pipex->fd2[0]);
		close(pipex->fd2[1]);
		return ;
	}
}

void	there_is_pipe(t_struct *ms, char *prompt)
{
	t_pid	*all_pid;
	t_pipe	*pipex;
	int		test[ms->parsing.nb_pipe][2];
	int		i;
	int		j;
	int		k;
	int		l;
	int		len;
	char	**cmd_pipe;
	char	**new_args;

	i = 0;
	j = 0;
	all_pid = malloc(sizeof(t_pid));
	if (all_pid == NULL)
		return ;
	pipex = malloc(sizeof(t_pipe));
	if (pipex == NULL)
		return ;
	pipex->pipe_tot = ms->parsing.nb_pipe;
	pipex->pipe_nbr = 1;
	pipex->cmd_nbr = 0;
	cmd_pipe = get_cmd_and_args_split(&prompt[i]);
	len = len_tab(cmd_pipe);
	pipex->pipe = 0;
	while (j < pipex->pipe_tot)
	{
		if (pipe(test[j]) == -1)
			return ;
		j++;
	}
	while (i < len)
	{
		l = 0;
		pipe_left_right(pipex);
		if (init_fork(&pipex->pid) == -1)
			return ;
		// add_nbr_back(&all_pid, pipex->pid);
		new_args = get_good_args_for_cmd(ms, &cmd_pipe[i]);
		if (pipex->pid == 0)	// child
			child_process(ms, pipex, new_args, test);
		else
		{
			if (pipex->pipe_tot == 1 && pipex->cmd_nbr == 1)	// ATTENTION ! FONCTIONNE !
				close(test[0][1]);								// ATTENTION ! FONCTIONNE !
			while (l < pipex->pipe - 1)
			{
				close(test[l][0]);
				close(test[l][1]);
				l++;	// a la fin, sur pipe - 1
			}
			if (pipex->pipe_left == 0 && l < pipex->pipe_tot)
			{
				close(test[l][0]);	// sur pipe - 1
				close(test[l][1]);	// sur pipe - 1
			}
			l += 2;	//sur pipe + 1
			while (l < pipex->pipe_tot)
			{
				close(test[l][0]);
				close(test[l][1]);
				l++;
			}
		}
		i += pass_previous_cmd(&cmd_pipe[i], ms);
		ft_free_tab(new_args);
		pipex->cmd_nbr++;
		pipex->pipe++;
	}
	// print_struct_pid(&all_pid);
	k = -1;
	while (k < pipex->pipe_tot)
	{
		// wait(NULL);
		waitpid(all_pid->pid, &pipex->status, 0);
		// all_pid = all_pid->next;		// mybe not...
		k++;
	}
	dup2(STDOUT_FILENO, STDIN_FILENO);	// maybe not...
}

/*

Commandes a tester =>

ls -l | wc -cl
ls | wc
ls | sort
cat /dev/urandom | head -c 1000 | wc -c
cat a_trier | sort | uniq

En trouver d'autres...

*/