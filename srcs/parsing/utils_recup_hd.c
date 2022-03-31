/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_recup_hd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:02:22 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/31 15:22:47 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_var_hd(char *line, t_struct *minish)
{
	int	i;

	i = 0;
	minish->parsing.len_arg = 0;
	while (line[i])
	{
		if (line[i] == '$')
			i += len_variable(&line[i], minish);
		else
			minish->parsing.len_arg++;
		i++;
	}
	return (i);
}

char	*fill_var_hd(char *line, char *str, t_struct *minish)
{
	int	i;

	i = 0;
	minish->parsing.fill_arg = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '$')
			i += fill_variable(&line[i], str, minish);
		else
			str[minish->parsing.fill_arg++] = line[i];
		i++;
	}
	str[minish->parsing.fill_arg] = '\0';
	return (str);
}

char	*get_var_hd(char *line, t_struct *minish)
{
	char	*str;
	int		i;

	i = len_var_hd(line, minish);
	str = malloc(sizeof(char) * (minish->parsing.len_arg + 1));
	ft_bzero(str, minish->parsing.len_arg + 1);
	str = fill_var_hd(line, str, minish);
	return (str);
}
