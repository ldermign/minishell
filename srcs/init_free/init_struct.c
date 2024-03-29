/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:29:11 by ldermign          #+#    #+#             */
/*   Updated: 2022/04/02 15:36:41 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_last_right(char **redir)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (redir[i])
	{
		if (redir[i][0] && redir[i][0] == '>')
		{
			if (redir[i][1] && redir[i][1] != '>')
				last = 1;
			else if (redir[i][1] && redir[i][1] == '>')
				last = 3;
		}
		i++;
	}
	return (last);
}

void	init_struct_std(t_args *stack, t_red_std *std, int which)
{
	std->fd_to_read = 0;
	std->fd_to_write = 0;
	std->last_right = pos_last_redir_right(stack->redir);
	std->last_left = pos_last_redir_left(stack->redir);
	std->last = -1;
	if (std->last_right > std->last_left)
		std->last = get_last_right(stack->redir);
	else if (std->last_right < std->last_left)
		std->last = 2;
	std->which = which;
	std->right = is_redir(stack->redir, ">");
	std->dbl_r = is_redir(stack->redir, ">>");
	std->left = is_redir(stack->redir, "<");
	std->dbl_l = 0;
	if (ft_pos_strstr(stack->command, "<<") != -1)
		std->dbl_l = 1;
	std->both = 0;
	if (std->right == 1 && std->left == 1)
		std->both = 1;
	std->name_file = NULL;
}

void	init_struct_it(t_it *it)
{
	it->i = 0;
	it->j = 0;
	it->k = 0;
	it->l = 0;
	it->right = 0;
	it->right_right = 0;
	it->left = 0;
	it->left_left = 0;
	it->last = 0;
	it->pos = 0;
	it->add = 0;
	it->ret = 0;
	it->len = 0;
	it->bin = 0;
	it->equal = 0;
	it->tmp1 = NULL;
	it->tmp2 = NULL;
	it->str = NULL;
}

void	init_struct_pipe(t_pipe *pipe, t_struct *ms)
{
	pipe->pipe_tot = ms->parsing.nb_pipe;
	pipe->cmd_nbr = 0;
	pipe->nbr_exec = 0;
	pipe->fd_to_read = 0;
	pipe->fd_to_write = 0;
}

void	init_struct_execute(t_struct *ms, t_execute *exec, char **cmd)
{
	exec->new_env = NULL;
	exec->paths = NULL;
	exec->str_path = NULL;
	exec->new_env = get_new_env(ms->env.env_ms);
	exec->paths = ft_split(get_pwd_and_path(exec->new_env, "PATH="), ':');
	if (exec->paths != NULL && cmd != NULL)
		exec->str_path = working_path(exec->paths, cmd[0]);
	else if (exec->str_path == NULL && cmd != NULL && exec->paths == NULL)
		exec->str_path = ft_strdup(cmd[0]);
	else
		exec->str_path = NULL;
}
