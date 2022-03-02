/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:42:38 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/02 18:01:57 by ejahan           ###   ########.fr       */
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
	// printf("count redir = %d\n",count_redir(minish->args->first->command));
	// minish->args = new_list(minish->args);
	// print_list(minish->args);
	if (minish->args->first->arg_to_pass
		&& ft_memcmp(minish->args->first->arg_to_pass[0], "echo", 5) == 0)
	{
		minish->parsing.result = recup_echo(minish->args->first->arg_to_pass, minish);
		printf("echo = [%s]\n", minish->parsing.result);
	}
	// print_list(minish->args);
	// free_list(minish->args);
	return (0);
}

int	recup_args(char *line, t_struct *minish)
{
	t_args	*tmp;
	// int	i = 0;

	if (recup_pipe(line, minish) == -1)
		return (-1);
	print_list(minish->args);
	minish->args = reverse_list(minish->args);
	print_list(minish->args);
	tmp = minish->args->first;
	while (minish->args->first != NULL)
	{
		// printf("\n\n");
		// printf("arg = [%s]\n", minish->args->first->command);
		minish->parsing.nb_arg = 0;
		minish->args->first->arg_to_pass = sep_and_check_args(minish->args->first, minish);
		minish->args->first->redir = recup_redir(minish->args->first->command, minish);
		if (minish->parsing.error == 1)
		{
			minish->args->first = tmp;
			return (-1);
		}
		minish->args->first = minish->args->first->next;
	}
	// i = 0;
	minish->args->first = tmp;
	// while (minish->args->first->arg_to_pass[i] != NULL)
	// {
	// 	printf("[%s]\n", minish->args->first->arg_to_pass[i]);
	// 	printf("oui\n");
	// 	i++;
	// }
	return (0);
}
