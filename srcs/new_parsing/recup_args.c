/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:33:48 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/14 00:38:01 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	recup_pipe2(char *line, t_struct *minishell, int i)
{
	int		j;
	char	*str;

	str = malloc(sizeof(char) * i + 1);
	if (str == NULL)
	{
		printf("error malloc\n");
		minishell->parsing.error = 1;
		return (-2);
	}
	j = i;
	str[i] = '\0';
	i--;
	while (i >= 0)
	{
		str[i] = line[minishell->parsing.i_line + i];
		i--;
	}
	minishell->parsing.i_line += j;
	insertion(minishell->args, str);
	minishell->parsing.i_line++;
	return (i);
}

int	recup_pipe(char *line, t_struct *minishell)
{
	int		i;

	while (line[minishell->parsing.i_line])
	{
		i = 0;
		minishell->parsing.nb_pipe++;
		while (line[minishell->parsing.i_line + i]
			&& line[minishell->parsing.i_line + i] != '|')
			i++;
		if (recup_pipe2(line, minishell, i) == -2)
			return (-1);
	}
	return (0);
}

static int	count_args(char *line, t_struct *minishell)
{
	int	i;

	i = 0;
	return (i);
}

static int	sep_args(char *line, t_struct *minishell)
{
	int	i;

	i = count_args(line, minishell);
	if (i == -1)
		return (-1);
	return (0);
}

int	recup_args(char *line, t_struct *minishell)
{
	if (recup_pipe(line, minishell) == -1)
		return (-1);
	minishell->pasing.tab_args = malloc(sizeof(char *) * minishell->parsing.nb_pipe + 1);
	minishell->pasing.tab_args[minishell->parsing.nb_pipe] = NULL;
	if (minishell->pasing.tab_args == NULL)
	{
		printf("error malloc\n");
		minishell->parsing.error = 1;
		return (-1);
	}
	if (sep_args(line, minishell) == -1)
		return (-1);
	return (0);
}
