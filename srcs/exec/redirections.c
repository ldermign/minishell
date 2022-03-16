/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:44:31 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/16 16:00:07 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	good_fd_for_redir(t_args *stack, t_red_std *std)
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

char	*get_name_left(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '>' || str[i] == '<'))
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	return (&str[i]);
}

int	good_fd_for_redir_with_pipe(t_args *stack, t_red_std *std, t_pipe *pipex)
{(void)stack;(void)std;(void)pipex;
	//	ici, on est sur que y'a des pipes
	//	on est dans le child
	//	on est pas a la premiere commande
	//	
	//	pour <
	//	si c'est un built_in, on s'en fout de recup le stdin
	//	sinon, recup
	//	dans les deux cas, rien ne sera sur le prompt, plus de stdout (reset dup2 ?)
	//	
	//	pour > et >>, toujours ecrire dans le fichier
	//	si les deux
	//	osef du stdin pour les built-in, sinon, relou
	// int	pipe_tmp[2];

	// if (pipe(pipe_tmp) == -1)
	// {
	// 	perror("pipe");
	// 	return (EXIT_FAILURE);
	// }
	char	*tmp;

	tmp = NULL;
	if (std->both == 0)
	{
		if (std->which == 1)		// >
			std->fd_to_write = open(std->name_file, O_WRONLY | O_TRUNC, 0644);
		else if (std->which == 3)	// >>
			std->fd_to_write = open(std->name_file, O_WRONLY | O_APPEND, 0644);
		if (std->which == 1 || std->which == 3)
			dup2(std->fd_to_write, STDOUT_FILENO);	// clooose ??
		if (std->which == 2)
		{
			tmp = get_name_left(stack->redir[std->last_left]);
			std->fd_to_read = open(tmp, O_RDONLY);
			dup2(std->fd_to_read, 0);
		}
	}
	// else
	// {

	// }
	if (std->fd_to_write == -1 || std->fd_to_read == -1)
	{
		perror("fd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	execute_redirection_built_in_or_execve(t_struct *ms, t_args *stack, t_red_std *std)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		g_sig_error = 127;
		perror("fork");
		return (EXIT_FAILURE);
	}
	signal(SIGINT, handle_signal_child);
	signal(SIGQUIT, handle_signal_child);
	if (pid == 0)
	{
		good_fd_for_redir(stack, std);
		if (is_built_in(stack->arg_to_pass[0]) == EXIT_SUCCESS)
			built_in(ms, stack);
		else
			execute_cmd_execve(ms, stack->arg_to_pass);
		g_sig_error = 0;
		exit (0);
	}
	else
	{
		ms->pid = pid;
		wait(NULL);
	}
	return (EXIT_SUCCESS);
}

int	redirection(t_struct *ms, t_args *stack, t_pipe	*pipex)
{
	int			i;
	int			j;
	int			ret;
	t_red_std	fd_redir;

	ret = 0;
	if (!ft_is_alpha(stack->arg_to_pass[0][0]))
		return (1);
	init_struct_std(stack->redir, &fd_redir, last_redir(stack->redir));
	i = 0;
	while (stack->redir[i + 1])
		i++;
	j = 0;
	while (stack->redir[i][j] == ' '
		|| stack->redir[i][j] == '>' || stack->redir[i][j] == '<')
		j++;
	fd_redir.name_file = &(stack->redir[i][j]);
	if (&pipe == NULL)
		return (execute_redirection_built_in_or_execve(ms, stack, &fd_redir));
	good_fd_for_redir_with_pipe(stack, &fd_redir, pipex);
	if (is_built_in(stack->arg_to_pass[0]) == EXIT_FAILURE)
		ret = execute_cmd_execve(ms, stack->arg_to_pass);
	else
		ret = built_in(ms, stack);
	if (fd_redir.fd_to_read != 0)
		close(fd_redir.fd_to_read);
	if (fd_redir.fd_to_write != 0)
		close(fd_redir.fd_to_write);
	exit (ret);
}