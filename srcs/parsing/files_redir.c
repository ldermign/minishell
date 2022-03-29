/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 02:54:17 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/29 11:02:13 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_file(char *args, t_struct *minish)
{
	int		fd;
	char	*name_file;

	name_file = recup_name(args);
	fd = open(name_file, O_CREAT, 0644);
	if (fd == -1)
	{
		minish->parsing.error = 1;
		fprintf(stderr, "error create file\n");
		return ;
	}
	close(fd);
	free(name_file);
}

void	check_file(char *arg, t_struct *minish)
{
	int	i;
	int	fd;

	i = 0;
	while (arg[i] && arg[i] != ' ')
		i++;
	while (arg[i] && arg[i] == ' ')
		i++;
	fd = open(&arg[i], O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "%s: No such file or directory\n", &arg[i]);
		g_sig_error = 1;
		minish->parsing.error = 1;
	}
	else
		close(fd);
}

void	redirections(t_list_arg *args, t_struct *minish)
{
	t_args		*tmp;
	int			i;

	tmp = args->first;
	while (args->first != NULL)
	{
		i = 0;
		while (args->first->redir[i] != NULL)
		{
			if (args->first->redir[i][0] == '>')
				create_file(args->first->redir[i], minish);
			else
				check_file(args->first->redir[i], minish);
			i++;
			if (minish->parsing.error != 0)
			{
				args->first = tmp;
				return ;
			}
		}
		args->first = args->first->next;
	}
	args->first = tmp;
}
