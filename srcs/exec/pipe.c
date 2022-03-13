/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:46:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/14 00:13:24 by ldermign         ###   ########.fr       */
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

void	cmd_execve(t_struct *ms, char **cmd)
{
	char	*str_path;

	str_path = working_path(ms->env.path, cmd[0]);
	// fprintf(stderr, "8\n");
	if (execve(str_path, cmd, ms->env.env_bash) == -1)
	{
		printf("minishell: %s: command not found\n", cmd[0]);
		g_sig_error = 127;
		// creer fonction qui close all
		// freeetoutbalalandls
		return ;
	}
}

void	child_process(t_pipe *pipex)
{
	if (pipex->cmd_nbr == 0)
	{
		dup2(pipex->fd0[1], STDOUT_FILENO);
		close(pipex->fd0[1]);
		close(pipex->fd0[0]);

	}
	else if (pipex->cmd_nbr % 2 == 0)
	{
		dup2(pipex->fd1[0], STDIN_FILENO);
		close(pipex->fd1[0]);
		close(pipex->fd1[1]);
		if (pipex->cmd_nbr != pipex->pipe_tot)
		{
			dup2(pipex->fd0[1], STDOUT_FILENO);
			close(pipex->fd0[1]);
			close(pipex->fd0[0]);
		}
	}
	else
	{
		dup2(pipex->fd0[0], STDIN_FILENO);
		close(pipex->fd0[0]);
		close(pipex->fd0[1]);
		if (pipex->cmd_nbr != pipex->pipe_tot)
		{
			dup2(pipex->fd1[1], STDOUT_FILENO);
			close(pipex->fd1[1]);
			close(pipex->fd1[0]);
		}
	}
}

void	close_fd_main(t_pipe * pipex)
{
	if (pipex->cmd_nbr != 0 && pipex->cmd_nbr % 2 == 0)
	{
		close(pipex->fd1[0]);
		close(pipex->fd1[1]);
	}
	else if (pipex->cmd_nbr % 2 != 0)
	{
		close(pipex->fd0[0]);
		close(pipex->fd0[1]);
	}
}

void	no_built_in_execve(t_pipe *pipex)
{
	if (init_fork(&pipex->pid) == -1) // checker ici si built in, parce que sinon, pas fork
		return ;
	if (pipex->pid == 0)
		child_process(pipex);
	else
		close_fd_main(pipex);
}

void	there_is_pipe(t_struct *ms)
{
	t_pipe	*pipex;
	t_args	*stack;
	int		ret_built_in;
	int		i;

	stack = ms->args->first;
	pipex = malloc(sizeof(t_pipe));
	if (pipex == NULL)
		return ;
	init_struct_pipe(pipex, ms);
	while (stack)
	{
		ret_built_in = is_built_in(stack->arg_to_pass[0]);
		if (pipex->cmd_nbr != pipex->pipe_tot && pipex->cmd_nbr % 2 == 0)
		{
			if (pipe(pipex->fd0) == -1)
			{
				perror("pipe fd0:");
				return ;
			}
		}
		else if (pipex->cmd_nbr != pipex->pipe_tot && pipex->cmd_nbr % 2 != 0)
		{
			if (pipe(pipex->fd1) == -1)
			{
				perror("pipe fd1:");
				return ;
			}
		}
		if (ret_built_in == EXIT_FAILURE)
		{
			pipex->nbr_exec++;
			no_built_in_execve(pipex);				// redir ?
			if (pipex->pid == 0)
				cmd_execve(ms, stack->arg_to_pass);
		}
		else if (ret_built_in == EXIT_SUCCESS)
		{
			// fprintf(stderr, "2 fois putain !!\n");
			// yes_built_in(ms, stack, pipex);			// redir ?
			built_in_with_pipe(ms, stack, pipex);
			// close_fd_main(pipex);
		}
		// fprintf(stderr, "5\n");
		stack = stack->next;
		pipex->cmd_nbr++;
		pipex->pipe++;
	}
	i = 0;
	while (i < pipex->nbr_exec)
	{
		// fprintf(stderr, "1 fois\n");
		wait(NULL);
		i++;
	}

	// fprintf(stderr, "ici\n");
	dup2(STDOUT_FILENO, STDIN_FILENO);
	free(pipex);
	// fprintf(stderr, "[FIN DE LA BOUCLE]\n");
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