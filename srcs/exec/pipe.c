/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:46:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/02 18:21:01 by ldermign         ###   ########.fr       */
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
	if (pid == 0) // child
	{
		close(pipe_fd[0]);
		if (ms->pipe_left == 1)
			dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		if (execve(working_path(ms->env.path, cmd[0]), cmd, env) == -1)
		{
			printf("minishell: %s: command not found\n", cmd[0]);
			sig_error = 127;
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			return ;
		}
	}
	else // father
	{
		close(pipe_fd[1]);
		if (ms->pipe_left == 1)
			dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	// printf("pipe_fd[0] = %d, pipe_fd[1] = %d\n", pipe_fd[0], pipe_fd[1]);
	// if (pipe_fd[0] != -1)
	// 	close(pipe_fd[0]);
	// if (ms->TEST_PIPE_MERDE == 0 && pipe_fd[1] != -1)
	// 	close(pipe_fd[1]);
	// printf("pipe_fd[0] = %d, pipe_fd[1] = %d\n", pipe_fd[0], pipe_fd[1]);
	sig_error = 0;
}

int		init_pipe(int fd[2][2])
{
	if (pipe(fd[0]) == -1 || pipe(fd[1]) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (1);
}

int		init_fork(int *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		sig_error = 127;
		perror("fork");
		return (-1);
	}
	return (1);
}

void	child_process(t_struct *ms, int pipe_fd[2][2], char **cmd, int cmd_nbr)
{
	int			pipe_nbr;

	pipe_nbr = 1;
	if (cmd_nbr % 2 == 0)
		pipe_nbr = 0;
	if (cmd_nbr == 0)
	{
		// on close le 2eme pipe dont on a pas besoin pour la premiere commande
		// premiere boucle, je close le read puisqu'elle va lire au meme emplacement
		// je dup le out puisqu'elle va ecrire dans le pipe
		// je close l'ecriture
		// close(STDIN_FILENO);
		close(pipe_fd[1][0]);
		close(pipe_fd[1][1]);
		close(pipe_fd[0][0]);
		dup2(pipe_fd[0][1], STDOUT_FILENO);
		close(pipe_fd[0][1]);
		execve(working_path(ms->env.path, cmd[0]), cmd, ms->env.env_bash);
		return ;
	}
	// else if (ms->parsing.nb_pipe == cmd_nbr)
	// {
		close(pipe_fd[0][1]);	// on ecrit plus la
		dup2(pipe_fd[1][0], pipe_fd[0][0]);	// doit lire le pipe d'avant
		close(pipe_fd[1][0]);
		dup2(pipe_fd[1][1], STDOUT_FILENO);
		close(pipe_fd[1][1]);
		// close(pipe_fd[0][0]);
		// dup2(STDOUT_FILENO, STDIN_FILENO);
	// }
	// else if (ms->pipe_left == 1 && ms->pipe_right == 1)
	// {
	// 	return ;
	// 	// 2 pipes ?
	// }
	if (execve(working_path(ms->env.path, cmd[0]), cmd, ms->env.env_bash) == -1)
	{
		printf("minishell: %s: command not found\n", cmd[0]);
		sig_error = 127;
		close(pipe_fd[0][0]);
		close(pipe_fd[0][1]);
		close(pipe_fd[1][0]);
		close(pipe_fd[1][1]);
		return ;
	}
}

void	there_is_pipe(t_struct *ms, char *prompt)
{
	int		i;
	int		fd[2][2];
	int		pid;
	int		cmd_nbr;
	char	**cmd_pipe;
	char	**new_args;

	i = 0;
	cmd_nbr = 0;
	cmd_pipe = get_cmd_and_args_split(&prompt[i]);
	int len = len_tab(cmd_pipe);
	if (init_fork(&pid) == -1 || init_pipe(fd) == -1)
		return ;
	while (i < len)
	{
		// write(STDOUT_FILENO, &cmd_nbr, sizeof(int));
		new_args = get_good_args_for_cmd(ms, &cmd_pipe[i]);
		if (pid == 0)	// child
			child_process(ms, fd, new_args, cmd_nbr);
		else
		{
			close(fd[0][0]);
			close(fd[0][1]);
			close(fd[1][0]);
			close(fd[1][1]);
		}
		i += pass_previous_cmd(&cmd_pipe[i], ms);
		ft_free_tab(new_args);
		cmd_nbr++;
	}
	// dup2(STDOUT_FILENO, STDIN_FILENO);	//checker si toujours acces stdin
	// printf("bah alors...\n");
	// waitpid(pid, NULL, 0);
	// faire une fonction qui attend la fin de toustes les commandes
}

/*

Commandes a tester =>

ls -l | wc -cl
ls | wc
ls | sort
cat /dev/urandom | head -c 1000 | wc -c

En trouver d'autres...

*/

// tab[0] = ls
// tab[1] = -l

// // 2eme tour

// tab[0] = wc
// tab[1] =