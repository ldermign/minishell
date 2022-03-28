/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:44:31 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/28 14:09:52 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	both_redirections(t_red_std *std, char **args)
// {
// 	std->fd_to_read = open(args[std->last_left + 1], O_RDONLY, 0644);
// 	if (std->which == 1)
// 		std->fd_to_write = open(std->name_file, O_WRONLY | O_TRUNC, 0644);
// 	else
// 		std->fd_to_write = open(std->name_file, O_WRONLY | O_APPEND, 0644);
// 	dup2(std->fd_to_read, 0);
// 	dup2(std->fd_to_write, 1);
// }

// if (pipe(pipefd) == -1)
// {
// 	perror("pipe fd");
// 	return (EXIT_FAILURE);
// }
// line = readline("> ");
// while (ft_strcmp(line, stack->arg_to_pass[std->last_left + 1]) != 0)
// {
// 	write(pipefd[1], line, ft_strlen(line));
// 	write(pipefd[1], "\n", 1);
// 	line = readline("> ");
// }
// dup2(pipefd[0], STDIN_FILENO);
// close(pipefd[1]);

char	*get_good_string(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && (str[i] == '>' || str[i] == '<'))
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	return (&str[i]);
}

static int	good_fd_for_redir(t_args *stack, t_red_std *std)
{
	int		pipefd[2];
	char	*str;
	char	*line;

	str = NULL;
	line = NULL;
	if (std->both == 0)
	{
		if (std->which == 1)
			std->fd_to_write = open(std->name_file, O_WRONLY | O_TRUNC, 0644);
		else if (std->which == 3)
			std->fd_to_write = open(std->name_file, O_WRONLY | O_APPEND, 0644);
		if (std->which == 1 || std->which == 3)
		{
			dup2(std->fd_to_write, 1);
			close(std->fd_to_write);
		}
		if (std->which == 2)
		{
			str = get_good_string(stack->redir[std->last_left]);
			std->fd_to_read = open(str, O_RDONLY);
			dup2(std->fd_to_read, 0);
			// close(std->fd_to_read);
		}
		else if (std->which == 4)
		{
			int	i = 0;
			if (pipe(pipefd) == -1)
			{
				perror("pipe fd");
				return (EXIT_FAILURE);
			}
			// fprintf(stderr, "merde\n");
			while (stack->args_here_doc[i])
			{
				write(pipefd[1], stack->args_here_doc[i], ft_strlen(stack->args_here_doc[i]));
				write(pipefd[1], "\n", 1);
				i++;
			}
			// ft_free_tab_char(stack->args_here_doc);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[1]);
		}
	}
	else if (std->both == 1)
	{
		str = get_good_string(stack->redir[std->last_left]);
		std->fd_to_read = open(str, O_RDONLY, 0644);
		if (std->which == 1)
			std->fd_to_write = open(std->name_file, O_WRONLY | O_TRUNC, 0644);
		else
			std->fd_to_write = open(std->name_file, O_WRONLY | O_APPEND, 0644);
		dup2(std->fd_to_read, 0);
		close(std->fd_to_read);
		dup2(std->fd_to_write, 1);
		close(std->fd_to_write);
	}
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
{
	(void)stack;
	(void)std;
	(void)pipex;
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
	int		pipefd[2];
	char	*tmp;
	char	*str;

	tmp = NULL;
	str = NULL;
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
		else if (std->which == 4)
		{
			int	i = 0;
			if (pipe(pipefd) == -1)
			{
				perror("pipe fd");
				return (EXIT_FAILURE);
			}
			// fprintf(stderr, "merde\n");
			while (stack->args_here_doc[i])
			{
				write(pipefd[1], stack->args_here_doc[i], ft_strlen(stack->args_here_doc[i]));
				write(pipefd[1], "\n", 1);
				i++;
			}
			// ft_free_tab_char(stack->args_here_doc);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[1]);
		}
	}
	else if (std->both == 1)
	{
		str = get_good_string(stack->redir[std->last_left]);
		std->fd_to_read = open(str, O_RDONLY, 0644);
		if (std->which == 1)
			std->fd_to_write = open(std->name_file, O_WRONLY | O_TRUNC, 0644);
		else
			std->fd_to_write = open(std->name_file, O_WRONLY | O_APPEND, 0644);
		dup2(std->fd_to_read, 0);
		close(std->fd_to_read);
		dup2(std->fd_to_write, 1);
		close(std->fd_to_write);
	}
	if (std->fd_to_write == -1 || std->fd_to_read == -1)
	{
		perror("fd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	execute_redirection_built_in_or_execve(t_struct *ms, t_args *stack,
	t_execute *exec, t_red_std *std)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		g_sig_error = 127;
		return (g_sig_error);
	}
	signal(SIGINT, handle_signal_child);
	signal(SIGQUIT, handle_signal_child);
	if (pid == 0)
	{
		good_fd_for_redir(stack, std);
		if (is_built_in(stack->arg_to_pass[0]) == EXIT_SUCCESS)
		{
			ft_free_struct_execute(exec);
			built_in(ms, stack);
			free_list(ms->args);
			ft_free_all(ms);
		}
		else
			execute_cmd_execve(ms, exec, stack->arg_to_pass);
		// ft_free_struct_execute(exec);
		exit (0);
	}
	else
	{
		ft_free_struct_execute(exec);
		ms->pid = pid;
		wait(NULL);
	}
	g_sig_error = 0;
	return (g_sig_error);
}

int	redirection(t_struct *ms, t_args *stack, t_pipe	*pipex)
{
	int			i;
	int			j;
	int			ret;
	t_execute	exec;

	ret = 0;
	if (stack->arg_to_pass != NULL && !ft_is_alpha(stack->arg_to_pass[0][0]))
		return (1);
	i = 0;
	while (stack->redir && stack->redir[i] && stack->redir[i + 1])
		i++;
	j = 0;
	while (stack->redir && stack->redir[i] && (stack->redir[i][j] == ' '
		|| stack->redir[i][j] == '>' || stack->redir[i][j] == '<'))
		j++;
	if (stack->redir)
		ms->std.name_file = &(stack->redir[i][j]);
	init_struct_execute(ms, &exec, stack->arg_to_pass);
	if (ms->parsing.nb_pipe == 0)
		return (execute_redirection_built_in_or_execve(ms, stack, &exec, &(ms->std)));
	good_fd_for_redir_with_pipe(stack, &(ms->std), pipex);
	if (stack->arg_to_pass && is_built_in(stack->arg_to_pass[0]) == EXIT_FAILURE)
		ret = execute_cmd_execve(ms, &exec, stack->arg_to_pass);
	else if (stack->arg_to_pass && is_built_in(stack->arg_to_pass[0]) == EXIT_SUCCESS)
		ret = built_in(ms, stack);
	if (ms->std.fd_to_read != 0)
		close(ms->std.fd_to_read);
	if (ms->std.fd_to_write != 0)
		close(ms->std.fd_to_write);
	ft_free_struct_execute(&exec);
	if (ms->parsing.nb_pipe > 0)
	{
		free_list(ms->args);
		ft_free_all(ms);
	}
	return (ret);
}
