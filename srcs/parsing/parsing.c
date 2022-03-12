/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:42:38 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/12 05:05:05 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	redirections(t_struct *minish)
// {
// 	// creer les fichiers si '>' ou '>>'
// 	// verifier si les fichiers existent si '<'
// }

int	parsing(char *line, t_struct *minish)
{
	minish->args = init_args();
	init_parsing(&minish->parsing);
	if (recup_args(line, minish) == -1)
	{
		minish->args = reverse_list(minish->args);
		exec_here_doc(minish->args);
		if (minish->parsing.error == 2)
			free_list2(minish->args);
		if (minish->parsing.error == 3)
			free_list3(minish->args);
		return (-1);
	}
	// redirections(minish);
	// if (minish->parsing.error != 0)
	// {
	// 	free_list(minish->args);
	// 	return (-1);
	// }
	minish->parsing.nb_pipe -= 1;
	return (0);
}

int	recup_pipe(char *line, t_struct *minish)
{
	int	i;
	int	j;

	while (line[minish->parsing.i_line])
	{
		i = 0;
		j = 0;
		if (check_pipe2(&line[minish->parsing.i_line], minish) == -1)
			return (-1);
		while (line[minish->parsing.i_line + i]
			&& line[minish->parsing.i_line + i] != '|')
		{
			i += pass_arg(&line[minish->parsing.i_line + i], minish);
			if (minish->parsing.error != 0)
				return (-1);
		}
		recup_pipe2(line, minish, i);
		minish->parsing.nb_pipe++;
		if (minish->parsing.error != 0)
			return (-1);
		if (line[minish->parsing.i_line] != '\0')
			minish->parsing.i_line++;
	}
	return (0);
}

int	recup_args(char *line, t_struct *ms)
{
	t_args	*tmp;

	if (recup_pipe(line, ms) == -1)
		return (-1);
	ms->args = reverse_list(ms->args);
	exec_here_doc(ms->args);
	tmp = ms->args->first;
	while (ms->args->first != NULL)
	{
		ms->parsing.nb_arg = 0;
		ms->args->first->arg_to_pass = sep_and_check_args(ms->args->first, ms);
		if (ms->parsing.error != 0)
		{
			ms->args->first = tmp;
			return (-1);
		}
		ms->args->first->redir = recup_redir(ms->args->first->command, ms);
		if (ms->parsing.error != 0)
		{
			ms->args->first = tmp;
			return (-1);
		}
		ms->args->first = ms->args->first->next;
	}
	ms->args->first = tmp;
	return (0);
}
