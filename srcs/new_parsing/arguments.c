/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:39:00 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/16 05:41:37 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i][0] == '<' || str[i][0] == '>')
			j += 0;
		else if (str[i][0] == 39 && str[i][1] == 39)
			j += 0;
		else if (str[i][0] == 34 && str[i][1] == 34)
			j += 0;
		else
			j++;
		i++;
	}
	return (j);
}

int	interpret_args(t_struct *minish)
{
	int	i;

	i = count_args(minish->args->first->tab_args);
	printf("i = %d\n", i);
	// minish->args->first->arg_to_pass = malloc(sizeof(char *) * i + 1);
	// if (minish->args->first->arg_to_pass == NULL)
	// {
	// 	printf("error malloc\n");
	// 	minish->parsing.error = 1;
	// 	return (-1);
	// }
	// while (i > 0)
	// {
		
	// }
	return (0);
}
