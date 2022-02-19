/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_recup_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:26:27 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/20 00:18:55 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_good_fd(char **args, char *name_file, t_red_std *std, int ret)
{
	std->name_file = name_file;
	if (std->which == -1)
		return (EXIT_SUCCESS);
	if (std->both == 0)
	{
		if (std->which == 1)
			std->fd_to_write = open(std->name_file, O_WRONLY | O_TRUNC, 0644);
		else if (std->which == 3)
			std->fd_to_write = open(std->name_file, O_WRONLY | O_APPEND, 0644);
		if (ret == -1 && (std->which == 1 || std->which == 3))
			dup2(std->fd_to_write, 1);
		if (std->which == 2)
		{
			std->fd_to_read = open(args[std->last_left + 1], O_RDONLY);
			dup2(std->fd_to_read, 0);
		}
		// else if (std->which == 4)
		// {
		// 	std->fd_to_read = 1;
		// 	dup2(std->fd_to_read, 0);
		// }

	}
	else if (std->both == 1)	//	si les chevrons sont melanges
	{
		std->fd_to_read = open(args[std->last_left + 1], O_RDONLY, 0644);
		if (std->which == 1)
			std->fd_to_write = open(std->name_file, O_WRONLY | O_TRUNC, 0644);
		else
			std->fd_to_write = open(std->name_file, O_WRONLY | O_APPEND, 0644);
		dup2(std->fd_to_read, 0);
		dup2(std->fd_to_write, 1);
	}
	if (std->fd_to_write == -1 || std->fd_to_read == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}