/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:42:38 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/13 18:48:27 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *line, t_struct *minish)
{
	// (void)line;
	// printf("test\n");
	minish->args = init_args();
	init_parsing(&minish->parsing);
	recup_args(line, minish);
	// insertion(minish->args, line);
	print_list(minish->args);
	// printf("arg = %s\n", minish->args->first->arg);
	free_list(minish->args);
	return (0);
}
