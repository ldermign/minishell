/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:29:11 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/11 13:53:42 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct_std(char **args, t_red_std *std, int which)
{
	std->fd_to_read = 0;
	std->fd_to_write = 0;
	std->last_right = pos_last_redir_right(args);
	std->last_left = pos_last_redir_left(args);
	std->which = which;
	std->right = is_redir(args, ">");
	std->dbl_r = is_redir(args, ">>");
	std->left = is_redir(args, "<");
	std->dbl_l = is_redir(args, "<<");
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
	it->pos = 0;
	it->add = 0;
	it->ret = 0;
	it->len = 0;
}

void	init_struct_pipe(t_pipe *pipe, t_struct *ms)
{
	pipe->pipe = 0;
	pipe->pipe_tot = ms->parsing.nb_pipe;
	pipe->cmd_nbr = 0;
	pipe->nbr_exec = 0;
}
