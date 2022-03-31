/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:44:06 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/31 13:09:56 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	redir_is_here_doc(t_args *stack)
{
	int	i;
	int	pipefd[2];

	i = 0;
	if (pipe(pipefd) == -1)
	{
		perror("pipe fd");
		return ;
	}
	while (stack->args_here_doc[i])
	{
		write(pipefd[1], stack->args_here_doc[i],
			ft_strlen(stack->args_here_doc[i]));
		write(pipefd[1], "\n", 1);
		i++;
	}
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
}

static void	redir_is_both(t_args *stack, t_red_std *std)
{
	char	*str;

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

int	good_fd_for_redir(t_args *stack, t_red_std *std)
{
	if (std->both == 0)
	{
		if (std->which == 1)
			std->fd_to_write = open(std->name_file, O_WRONLY | O_TRUNC, 0644);
		else if (std->which == 3)
			std->fd_to_write = open(std->name_file, O_WRONLY | O_APPEND, 0644);
		if (std->which == 1 || std->which == 3)
			dup2(std->fd_to_write, STDOUT_FILENO);
		if (std->which == 2)
		{
			std->fd_to_read = open(get_name_left(stack->redir[std->last_left]),
					O_RDONLY);
			dup2(std->fd_to_read, 0);
		}
		else if (std->which == 4)
			redir_is_here_doc(stack);
	}
	else if (std->both == 1)
		redir_is_both(stack, std);
	if (std->fd_to_write == -1 || std->fd_to_read == -1)
	{
		perror("minishell: fd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
