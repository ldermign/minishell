/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:44:31 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/31 13:09:52 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child(t_struct *ms, t_args *stack, t_execute *exec,
	t_red_std *std)
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
	exit (0);
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
		handle_child(ms, stack, exec, std);
	else
	{
		ft_free_struct_execute(exec);
		ms->pid = pid;
		wait(NULL);
	}
	g_sig_error = 0;
	return (g_sig_error);
}

static void	execute_and_free(t_struct *ms, t_args *stack, t_execute *exec,
	int ret)
{
	if (stack->arg_to_pass
		&& is_built_in(stack->arg_to_pass[0]) == EXIT_FAILURE)
		ret = execute_cmd_execve(ms, exec, stack->arg_to_pass);
	else if (stack->arg_to_pass
		&& is_built_in(stack->arg_to_pass[0]) == EXIT_SUCCESS)
		ret = built_in(ms, stack);
	if (ms->std.fd_to_read != 0)
		close(ms->std.fd_to_read);
	if (ms->std.fd_to_write != 0)
		close(ms->std.fd_to_write);
	ft_free_struct_execute(exec);
	if (ms->parsing.nb_pipe > 0)
	{
		free_list(ms->args);
		ft_free_all(ms);
	}	
}

int	redirection(t_struct *ms, t_args *stack)
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
		return (execute_redirection_built_in_or_execve(ms, stack, &exec,
				&(ms->std)));
	good_fd_for_redir(stack, &(ms->std));
	execute_and_free(ms, stack, &exec, ret);
	return (ret);
}
