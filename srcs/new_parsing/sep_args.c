/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:53:30 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/16 05:59:13 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sep_and_check_args(t_args *arg, t_struct *minish)
{
	int	i;

	i = 0;
	i = count_args(arg, minish);
	arg->tab_args = malloc(sizeof(char *) * i + 1);
	if (arg->tab_args == NULL)
	{
		printf("error malloc\n");
		minish->parsing.error = 1;
		return (-1);
	}
	arg->tab_args[i] = NULL;
	if (interpret_args(minish) == -1)
		return (-1);
	return (0);
}

// int	sep_and_check_args(t_args *arg, t_struct *minish)
// {
// 	int	i;

// 	i = 0;
// 	arg->tab_args = ft_split(arg->command, ' ');
// 	if (arg->tab_args == NULL)
// 	{
// 		printf("error malloc\n");
// 		minish->parsing.error = 1;
// 		return (-1);
// 	}
// 	// while (arg->tab_args[i] != NULL)
// 	// {
// 	// 	printf("tab[%i] = [%s]\n", i, arg->tab_args[i]);
// 	// 	i++;
// 	// }
// 	if (interpret_args(minish) == -1)
// 		return (-1);
// 	return (0);
// }
