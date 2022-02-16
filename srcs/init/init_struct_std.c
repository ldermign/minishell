/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_std.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:29:11 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/16 14:37:16 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reboot_struct_std(t_red_std *std)
{
	close(std->fd_to_write);
	dup2(std->old_stdin, 0);
	dup2(std->old_stdout, 1);
	dup2(std->old_stderr, 2);
}

void	init_struct_std(char **args, t_red_std *std, int which)
{
	std->old_stdin = dup(0);
	std->new_stdin = 0;
	std->old_stdout = dup(1);
	std->new_stdout = 1;
	std->old_stderr = dup(2);
	std->new_stderr = 2;
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