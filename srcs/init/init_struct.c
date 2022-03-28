/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:29:11 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/28 14:01:02 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct_std(t_args *stack, t_red_std *std, int which)
{
	// print_tab_char(args);
	std->fd_to_read = 0;
	std->fd_to_write = 0;
	std->last_right = pos_last_redir_right(stack->redir);
	std->last_left = pos_last_redir_left(stack->redir);
	std->which = which;
	// fprintf(stderr, "WICHHHHH %d\n", std->which);
	std->right = is_redir(stack->redir, ">");	// 1
	std->dbl_r = is_redir(stack->redir, ">>");	// 3
	std->left = is_redir(stack->redir, "<");	// 2
	std->dbl_l = 0;
	if (ft_pos_strstr(stack->command, "<<") != -1)
		std->dbl_l = 1;							// 4
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
}

void	init_struct_pipe(t_pipe *pipe, t_struct *ms)
{
	pipe->pipe = 0;
	pipe->pipe_tot = ms->parsing.nb_pipe;
	pipe->cmd_nbr = 0;
	pipe->nbr_exec = 0;
	pipe->fd_to_read = 0;
	pipe->fd_to_write = 0;
}

void	init_struct_execute(t_struct *ms, t_execute *exec, char **cmd)
{
	exec->new_env = get_new_env(ms->env.env_ms);
	// print_tab_char(exec->new_env);
	exec->paths = ft_split(get_pwd_and_path(exec->new_env, "PATH="), ':');
	// print_tab_char(exec->paths);
	// fprintf(stderr, "cmd[0] = %s\n", cmd[0]);
	if (exec->paths != NULL && cmd != NULL)
		exec->str_path = working_path(exec->paths, cmd[0]);
	else
		exec->str_path = NULL;
	// printf("[%s]\n", exec->str_path);
}