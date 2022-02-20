/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:42:38 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/20 01:57:17 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *line, t_struct *minish)
{
	minish->args = init_args();
	init_parsing(&minish->parsing);
	// init_parsing(minish->new_parsing);
	recup_args(line, minish);
	// print_list(minish->args);
	free_list(minish->args);
	return (0);
}

int	recup_args(char *line, t_struct *minish)
{
	t_args	*tmp;
	// int	i = 0;

	if (recup_pipe(line, minish) == -1)
		return (-1);
	tmp = minish->args->first;
	while (minish->args->first != NULL)
	{
		printf("\n\n");
		printf("arg = [%s]\n", minish->args->first->command);
		minish->parsing.nb_arg = 0;
		if (sep_and_check_args(minish->args->first, minish) == -1)
			// || recup_redir(minish->args->first, minish) == -1)
		{
			minish->args->first = tmp;
			return (-1);
		}
		minish->args->first = minish->args->first->next;
	}
	// i = 0;
	// while (minish->args->first->arg_to_pass[i] != NULL)
	// {
	// 	printf("[%s]\n", minish->args->first->arg_to_pass[i]);
	// 	i++;
	// }
	minish->args->first = tmp;
	return (0);
}
