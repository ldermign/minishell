/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:42:38 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/14 00:29:14 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *line, t_struct *minish)
{
	minish->args = init_args();
	init_parsing(&minish->parsing);
	// init_parsing(minish->new_parsing);
	recup_args(line, minish);
	print_list(minish->args);
	free_list(minish->args);
	while (minishell->pasing.tab_args[i] != NULL)
		free(minishell->pasing.tab_args[i++]);
	free(minishell->pasing.tab_args);
	return (0);
}
