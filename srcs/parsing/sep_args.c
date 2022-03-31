/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:53:30 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/31 13:01:24 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char *line, t_struct *minish)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		i += pass_arg_count(&line[i], minish);
		if (minish->parsing.error != 0)
			return (-1);
	}
	return (i);
}

char	*fill_arg(char *line, char *str, t_struct *minish)
{
	len_arg(line, minish);
	if (minish->parsing.error != 0)
		return (NULL);
	str = malloc(sizeof(char) * (minish->parsing.len_arg + 1));
	if (str == NULL)
	{
		error_malloc(minish);
		return (NULL);
	}
	ft_bzero(str, minish->parsing.len_arg + 1);
	minish->parsing.i_line = fill_arg2(line, str, minish);
	return (str);
}

char	**interpret_args(char *line, char **tab_arg, t_struct *minish)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	minish->parsing.i_line = 0;
	while (line[i] && minish->parsing.nb_arg-- > 0)
	{
		tab_arg[j] = fill_arg(&line[i], tab_arg[j], minish);
		i += minish->parsing.i_line;
		if (minish->parsing.error != 0)
			return (NULL);
		while (line[i] == ' ')
			i++;
		j++;
	}
	return (tab_arg);
}

char	**sep_and_check_args(t_args *arg, t_struct *minish)
{
	int		i;
	char	**arg_to_pass;

	count_args(arg->command, minish);
	if (minish->parsing.error != 0)
		return (NULL);
	exec_here_doc(minish->args, minish);
	i = minish->parsing.nb_arg;
	if (i == 0)
		return (NULL);
	arg_to_pass = malloc(sizeof(char *) * (i + 1));
	if (arg_to_pass == NULL)
	{
		error_malloc(minish);
		return (NULL);
	}
	arg_to_pass[i] = NULL;
	arg_to_pass = interpret_args(arg->command, arg_to_pass, minish);
	if (minish->parsing.nb_arg != 0 && minish->parsing.error != 0)
	{
		free(arg_to_pass);
		return (NULL);
	}
	return (arg_to_pass);
}
