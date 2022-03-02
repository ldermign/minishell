/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:42:38 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/02 19:42:23 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *line, t_struct *minish)
{
	minish->args = init_args();
	init_parsing(&minish->parsing);
	if (recup_args(line, minish) == -1)
	{
		printf("\n\n\n\nERROR\n\n\n\n");
		return (-1);
	}
	if (minish->args->first->arg_to_pass
		&& ft_memcmp(minish->args->first->arg_to_pass[0], "echo", 5) == 0)
	{
		minish->parsing.result = recup_echo(minish->args->first->arg_to_pass, minish);
		printf("echo = [%s]\n", minish->parsing.result);
	}
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
			if (minish->parsing.error == 1)
				return (-1);
		}
		recup_pipe2(line, minish, i);
		minish->parsing.nb_pipe++;
		if (minish->parsing.error == 1)
			return (-1);
		if (line[minish->parsing.i_line] != '\0')
			minish->parsing.i_line++;
	}
	return (0);
}

// 27 lignes

int	recup_args(char *line, t_struct *minish)
{
	t_args	*tmp;

	if (recup_pipe(line, minish) == -1)
		return (-1);
	print_list(minish->args);
	minish->args = reverse_list(minish->args);
	print_list(minish->args);
	tmp = minish->args->first;
	while (minish->args->first != NULL)
	{
		minish->parsing.nb_arg = 0;
		minish->args->first->arg_to_pass = sep_and_check_args(minish->args->first, minish);
		if (minish->parsing.error == 1)
		{
			minish->args->first = tmp;
			return (-1);
		}
		minish->args->first->redir = recup_redir(minish->args->first->command, minish);
		if (minish->parsing.error == 1)
		{
			minish->args->first = tmp;
			return (-1);
		}
		minish->args->first = minish->args->first->next;
	}
	minish->args->first = tmp;
	return (0);
}
