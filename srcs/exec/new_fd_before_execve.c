/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_fd_before_execve.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:10:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/16 12:58:56 by ldermign         ###   ########.fr       */
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

static void	get_good_fd_built_in_norme(t_red_std *std, char **args)
{
	char	*line;

	if (std->which == 1)
		std->fd_to_write = open(std->name_file, O_WRONLY | O_TRUNC, 0644);
	else if (std->which == 3)
		std->fd_to_write = open(std->name_file, O_WRONLY | O_APPEND, 0644);
	if (std->which == 1 || std->which == 3)
		dup2(std->fd_to_write, 1);
	if (std->which == 2)
	{
		std->fd_to_read = open(args[std->last_left + 1], O_RDONLY);
		dup2(std->fd_to_read, 0);
	}
	else if (std->which == 4)
	{
		line = readline("> ");
		while (ft_strcmp(line, args[std->last_left + 1]) != 0)
			line = readline("> ");
	}
	if (std->which == 4)
		dup2(std->fd_to_read, 0);
}

int	get_good_fd_built_in(char **args, char *name_file, t_red_std *std)
{
	std->name_file = name_file;
	if (std->which == -1)
		return (EXIT_SUCCESS);
	if (std->both == 0)
		get_good_fd_built_in_norme(std, args);
	else if (std->both == 1)
		both_redirections(std, args);
	if (std->fd_to_write == -1 || std->fd_to_read == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
