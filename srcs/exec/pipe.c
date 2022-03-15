/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:46:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/15 15:31:56 by ldermign         ###   ########.fr       */
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

void	close_fd_child_main(t_pipe *pipex)
{
	if (pipex->cmd_nbr == 0)
	{
		close(pipex->fd0[0]);
		if (dup2(pipex->fd0[1], STDOUT_FILENO) < 0)
			perror("dup2");
		close(pipex->fd0[1]);
	}
	else if (pipex->cmd_nbr % 2 == 0)
	{
		if (dup2(pipex->fd1[0], STDIN_FILENO) < 0)
			perror("dup2");
		close(pipex->fd1[0]);
		if (pipex->cmd_nbr != pipex->pipe_tot)
		{
			close(pipex->fd0[0]);
			if (dup2(pipex->fd0[1], STDOUT_FILENO) < 0)
				perror("dup2");
			close(pipex->fd0[1]);
		}
	}
	else
	{
		if (dup2(pipex->fd0[0], STDIN_FILENO) < 0)
			perror("dup2");
		close(pipex->fd0[0]);
		if (pipex->cmd_nbr != pipex->pipe_tot)
		{
			close(pipex->fd1[0]);
			if (dup2(pipex->fd1[1], STDOUT_FILENO) < 0)
				perror("dup2");
			close(pipex->fd1[1]);
		}
	}
}

void	close_fd_pipe_main(t_pipe * pipex)
{
	if (pipex->cmd_nbr == 0)
		close(pipex->fd0[1]);
	else if (pipex->cmd_nbr % 2 == 0)
	{
		close(pipex->fd1[0]);
		if (pipex->cmd_nbr != pipex->pipe_tot)
			close(pipex->fd0[1]);
	}
	else if (pipex->cmd_nbr % 2 != 0)
	{
		close(pipex->fd0[0]);
		if (pipex->cmd_nbr != pipex->pipe_tot)
			close(pipex->fd1[1]);
	}
}

int	pipe_the_good_one(t_pipe *pipex)
{
	if (pipex->cmd_nbr != pipex->pipe_tot)
	{
		if (pipex->cmd_nbr % 2 == 0)
		{
			if (pipe(pipex->fd0) == -1)
			{
				perror("pipe fd0:");
				return (EXIT_FAILURE);
			}
		}
		else
		{
			if (pipe(pipex->fd1) == -1)
			{
				perror("pipe fd1:");
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}

static void	both_redirections(t_red_std *std, char **args)
{
	std->fd_to_read = open(args[std->last_left + 1], O_RDONLY, 0644);
	if (std->which == 1)
		std->fd_to_write = open(std->name_file, O_WRONLY | O_TRUNC, 0644);
	else
		std->fd_to_write = open(std->name_file, O_WRONLY | O_APPEND, 0644);
	dup2(std->fd_to_read, 0);
	dup2(std->fd_to_write, 1);
}

int	good_fd_for_redir(t_args *stack, t_red_std *std)
{
	if (std->both == 0)
	{
		if (std->which == 1)
			std->fd_to_write = open(std->name_file, O_WRONLY | O_TRUNC, 0644);
		else if (std->which == 3)
			std->fd_to_write = open(std->name_file, O_WRONLY | O_APPEND, 0644);
		if (std->which == 1 || std->which == 3)
			dup2(std->fd_to_write, 1);
		if (std->which == 2)
		{
			std->fd_to_read = open(stack->arg_to_pass[std->last_left + 1], O_RDONLY);
			dup2(std->fd_to_read, 0);
		}
		// else if (std->which == 4)
		// {
		// 	line = readline("> ");
		// 	while (ft_strcmp(line, stack->arg_to_pass[std->last_left + 1]) != 0)
		// 	{
		// 		write(pipefd[1], line, ft_strlen(line));
		// 		write(pipefd[1], "\n", 1);
		// 		line = readline("> ");
		// 	}
		// 	dup2(pipefd[0], STDIN_FILENO);
		// 	close(pipefd[1]);
		// }
	}
	else if (std->both == 1)
		both_redirections(std, stack->arg_to_pass);
	if (std->fd_to_write == -1 || std->fd_to_read == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	execute_redirection_built_in_or_execve(t_struct *ms, t_args *stack, t_red_std *std)
{
	int		status;
	pid_t	pid;

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
	if (pid == 0)
	{
		good_fd_for_redir(stack, std);
		if (is_built_in(stack->arg_to_pass[0]) == EXIT_SUCCESS)
			built_in_to_create(ms, stack);
		else
			cmd_execve(ms, stack->arg_to_pass);
		g_sig_error = 0;
		exit (0);
	}
	else
	{
		ms->pid = pid;
		wait(NULL);
	}

}

void	there_is_pipe(t_struct *ms)
{
	t_pipe	*pipex;
	t_args	*stack;
	int		i;

	stack = ms->args->first;
	pipex = malloc(sizeof(t_pipe));
	if (pipex == NULL)
		return ;
	init_struct_pipe(pipex, ms);
	while (stack)
	{
		if (pipe_the_good_one(pipex) == EXIT_FAILURE)
			exit (127); // pas le bon chiffre
		pipex->nbr_exec++;
		if (stack->redir[0] != NULL)
			redirection(ms, stack);
		if (init_fork(&pipex->pid) == -1)
		{
			perror("fork");
			return ;
		}
		if (pipex->pid == 0)
		{
			close_fd_child_main(pipex);
			if (stack->redir[0] != NULL)
				exit (0);
		}
		else
			close_fd_pipe_main(pipex);
		if (stack->redir[0] == NULL && pipex->pid == 0)
		{
			if (is_built_in(stack->arg_to_pass[0]) == EXIT_FAILURE)
				exit (cmd_execve(ms, stack->arg_to_pass));
			else
				exit (built_in_to_create(ms, stack));
		}
		stack = stack->next;
		pipex->cmd_nbr++;
		pipex->pipe++;
	}
	i = 0;
	while (i < pipex->nbr_exec)
	{
		wait(NULL);
		i++;
	}
	free(pipex);
}
