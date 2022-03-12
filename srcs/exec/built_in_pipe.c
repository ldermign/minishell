/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:27:50 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/12 18:23:01 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	yes_built_in(t_struct *ms, t_args *stack, t_pipe *pipex)
// {(void)ms;(void)stack;
// 	if (pipex->cmd_nbr == 0)
// 	{
// 		close(pipex->fd0[0]);
// 		dup2(pipex->fd0[1], STDOUT_FILENO);
// 		close(pipex->fd0[1]);
// 	}
// 	else if (pipex->cmd_nbr % 2 == 0)
// 	{
// 		close(pipex->fd1[1]);
// 		dup2(pipex->fd1[0], STDIN_FILENO);
// 		close(pipex->fd1[0]);
// 		if (pipex->cmd_nbr != pipex->pipe_tot)
// 		{
// 			close(pipex->fd0[0]);
// 			dup2(pipex->fd0[1], STDOUT_FILENO);
// 			close(pipex->fd0[1]);
// 		}
// 	}
// 	else
// 	{
// 		close(pipex->fd0[1]);
// 		dup2(pipex->fd0[0], STDIN_FILENO);
// 		close(pipex->fd0[0]);
// 		if (pipex->cmd_nbr != pipex->pipe_tot)
// 		{
// 			close(pipex->fd1[0]);
// 			dup2(pipex->fd1[1], STDOUT_FILENO);
// 			close(pipex->fd1[1]);
// 		}
// 	}
// }

void	write_in_pipe_for_built_in(t_pipe *pipex, char *str)
{
	if (pipex->cmd_nbr == 0)
	{
		if (write(pipex->fd0[1], str, ft_strlen(str)) < 0)
		{
			fprintf(stderr, "[%d]\n", errno);
			perror("write");
		}
		write(pipex->fd0[1], "\n", 1);
		// dup2(pipex->fd0[0], STDIN_FILENO);
		close(pipex->fd0[1]);
		close(pipex->fd0[0]);
	}
	else if (pipex->cmd_nbr % 2 == 0)
	{
		close(pipex->fd1[1]);
		dup2(pipex->fd1[0], STDIN_FILENO);
		close(pipex->fd1[0]);
		if (pipex->cmd_nbr != pipex->pipe_tot)
		{
			write(pipex->fd0[1], str, ft_strlen(str));
			close(pipex->fd0[1]);
			close(pipex->fd0[0]);
		}
	}
	else
	{
		close(pipex->fd0[1]);
		dup2(pipex->fd0[0], STDIN_FILENO);
		close(pipex->fd0[0]);
		if (pipex->cmd_nbr != pipex->pipe_tot)
		{
			write(pipex->fd1[1], str, ft_strlen(str));
			close(pipex->fd1[1]);
			close(pipex->fd1[0]);
		}
	}
}

void	pwd_pipe(t_pipe *pipex)
{
	char	actual_path[PATH_MAX];

	if (getcwd(actual_path, sizeof(actual_path)) != NULL)
		write_in_pipe_for_built_in(pipex, actual_path);
	else
	{
		g_sig_error = errno;
		perror("getcwd");
	}
}

// char	*env_stack_to_tab_char(t_env_ms *stack)
// {
// 	int	len;

// 	len = 0;
// 	while (stack)
// 	{

// 		stack = stack->var;
// 	}
// }

int	sum_all_str_in_stack(t_env_ms *stack)
{
	int	len;

	len = 0;
	while (stack)
	{
		len += ft_strlen(stack->var);
		stack = stack->next;
	}
	return (len);
}

char	*env_stack_to_tab_char(t_env_ms *stack)
{
	int		j;
	int		i;
	int		len;
	char	*dst;

	len = sum_all_str_in_stack(stack);
	dst = malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (stack && i < len)
	{
		j = 0;
		while (stack->var[j])
		{
			dst[j] = stack->var[j];
			j++;
		}
		i += j;
		dst[i] = '\n';
		i++;
		stack = stack->next;
	}
	dst[i] = '\0';
	return (dst);
}

void	env_pipe(t_env_ms *stack, t_pipe *pipex)
{
	char	*all_env;

	all_env = env_stack_to_tab_char(stack);
	if (all_env == NULL)
	// 	exit (0);
	// while (stack)
	// {
		// if (ft_pos_strstr(stack->var, "=") != -1)
		// 	write_in_pipe_for_built_in(pipex, stack->var);
		write_in_pipe_for_built_in(pipex, all_env);
	// 	stack = stack->next;
	// }
	free(all_env);
}

void	built_in_with_pipe(t_struct *ms, t_args *cmd, t_pipe *pipex)
{(void)ms;(void)cmd;(void)pipex;
	// pas cd
	if (ft_memcmp(cmd->arg_to_pass[0], "pwd", 4) == 0)
		pwd_pipe(pipex);
	else if (ft_memcmp(cmd->arg_to_pass[0], "env", 4) == 0)
		env_pipe(ms->env.env_ms, pipex);
}