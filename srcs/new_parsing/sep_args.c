/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:53:30 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/20 08:24:20 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char *line, t_struct *minish)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		i += pass_arg_count(&line[i], minish);
		if (minish->parsing.error == 1)
			return (-1);
	}
	return (i);
}

char	*fill_arg(char *line, char *str, t_struct *minish)
{
	len_arg(line, minish);
	str = malloc(sizeof(char) * minish->parsing.len_arg + 1);
	if (str == NULL)
	{
		error_malloc(minish);
		return (NULL);
	}
	ft_bzero(str, minish->parsing.len_arg + 1);
	fill_arg2(line, str, minish);
	return (str);
}

char	**interpret_args(char *line, char	**tab_arg, t_struct *minish)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		tab_arg[j] = fill_arg(&line[i], tab_arg[j], minish);
		i += pass_arg_count(&line[i], minish);
		if (minish->parsing.error == 1)
			return (NULL);
		printf("arg[%d] = [%s]\n", j, tab_arg[j]);
		while (line[i] == ' ')
			i++;
		j++;
	}
	// i = 0;
	// while (tab_arg[i] != NULL)
	// {
	// 	printf("[%s]\n", tab_arg[i]);
	// 	printf("oui\n");
	// 	i++;
	// }
	return (tab_arg);
}

char	**sep_and_check_args(t_args *arg, t_struct *minish)
{
	int		i;
	char	**arg_to_pass;

	count_args(arg->command, minish);
	if (minish->parsing.error == 1)
		return (NULL);
	i = minish->parsing.nb_arg;
	printf("nombre d arguments = %d\n", minish->parsing.nb_arg);
	arg_to_pass = malloc(sizeof(char *) * i + 1);
	if (arg_to_pass == NULL)
	{
		error_malloc(minish);
		return (NULL);
	}
	arg_to_pass[i] = NULL;
	arg_to_pass = interpret_args(arg->command, arg_to_pass, minish);
	if (minish->parsing.nb_arg != 0 && minish->parsing.error == 1)
	{
		free(arg_to_pass);
		return (NULL);
	}
	return (arg_to_pass);
}
