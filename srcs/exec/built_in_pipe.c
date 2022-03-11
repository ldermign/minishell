/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:27:50 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/11 16:01:57 by ldermign         ###   ########.fr       */
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
		// fprintf(stderr, "4 jusqu'a la fin\n");
		// fprintf(stderr, "fd0[0] == %d - fd0[1] == %d - fd1[0] == %d - fd1[1] == %d\n", pipex->fd0[0], pipex->fd0[1], pipex->fd1[0], pipex->fd1[1]);
		close(pipex->fd0[0]);
		// fprintf(stderr, "4bis\n");
		// fprintf(stderr, "%s\n", str);
		// fprintf(stderr, "alive ? %d\n", pipex->fd0[1]);
		fprintf(stderr, "fd0[0] == %d - fd0[1] == %d - fd1[0] == %d - fd1[1] == %d\n", pipex->fd0[0], pipex->fd0[1], pipex->fd1[0], pipex->fd1[1]);
		write(pipex->fd0[1], str, ft_strlen(str));
		fprintf(stderr, "4bisbis\n");
		close(pipex->fd0[1]);
		// fprintf(stderr, "4bisbisbis\n");
	}
	else if (pipex->cmd_nbr % 2 == 0)
	{
		close(pipex->fd1[1]);
		dup2(pipex->fd1[0], STDIN_FILENO);
		close(pipex->fd1[0]);
		if (pipex->cmd_nbr != pipex->pipe_tot)
		{
			close(pipex->fd0[0]);
			write(pipex->fd0[1], str, ft_strlen(str));
			close(pipex->fd0[1]);
		}
	}
	else
	{
		close(pipex->fd0[1]);
		dup2(pipex->fd0[0], STDIN_FILENO);
		close(pipex->fd0[0]);
		if (pipex->cmd_nbr != pipex->pipe_tot)
		{
			close(pipex->fd1[0]);
			write(pipex->fd1[1], str, ft_strlen(str));
			close(pipex->fd1[1]);
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

void	env_pipe(t_env_ms *stack, t_pipe *pipex)
{
	fprintf(stderr, "3\n");
	// char	*all_env;

	// all_env = env_stack_to_tab_char(stack);
	while (stack)
	{
		if (ft_pos_strstr(stack->var, "=") != -1)
			write_in_pipe_for_built_in(pipex, stack->var);
		stack = stack->next;
	}
	// free(all_env);
}

void	built_in_with_pipe(t_struct *ms, t_args *cmd, t_pipe *pipex)
{(void)ms;(void)cmd;(void)pipex;
	// pas cd
	fprintf(stderr, "2\n");
	if (ft_memcmp(cmd->arg_to_pass[0], "pwd", 4) == 0)
		pwd_pipe(pipex);
	else if (ft_memcmp(cmd->arg_to_pass[0], "env", 4) == 0)
		env_pipe(ms->env.env_ms, pipex);
}