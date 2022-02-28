/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 01:21:55 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/28 17:46:20 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pass_quotes_pipe(char *line, t_struct *minish)
{
	int	j;
	int	i;

	j = 0;
	i = 1;
	if (line[i] == line[j])
		return (i);
	while (line[i] && line[i] != line[j])
		i++;
	if (line[i] == '\0')
	{
		printf("error : open quotes\n");
		minish->parsing.error = 1;
		return (-1);
	}
	return (i);
}

int	pass_arg(char *line, t_struct *minish)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		while (line[i] && line[i] != 39 && line[i] != 34
			&& line[i] != ' ' && line[i] != '|')
			i++;
		if (line[i] == 39 || line[i] == 34)
			i += pass_quotes_pipe(&line[i], minish);
		else if (line[i] == '\0' || line[i] == ' ' || line[i] == '|')
			return (i);
		if (minish->parsing.error == 1)
			return (-1);
		i++;
	}
	return (i);
}

int	check_pipe2(char *line, t_struct *minish)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|' || line[i] == '\0')
	{
		printf("syntax error near unexpected token `|'\n");
		minish->parsing.error = 1;
		return (-1);
	}
	return (1);
}

int	check_pipe(char *line, t_struct *minish)
{
	int	i;

	i = 1;
	if (line[0] == '|')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '|' || line[i] == '\0')
		{
			printf("syntax error near unexpected token `|'\n");
			minish->parsing.error = 1;
			return (-1);
		}
	}
	return (1);
}

static int	recup_pipe2(char *line, t_struct *minish, int i)
{
	int		j;
	char	*str;

	if (check_pipe(&line[minish->parsing.i_line + i], minish) == -1)
		return (-1);
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (error_malloc(minish) - 1);
	j = i;
	str[i] = '\0';
	i--;
	while (i >= 0)
	{
		str[i] = line[minish->parsing.i_line + i];
		i--;
	}
	minish->parsing.i_line += j;
	insertion(minish->args, str);
	// minish->parsing.i_line++;
	return (i);
}

int	recup_pipe(char *line, t_struct *minish)
{
	int	i;
	int	j;

	while (line[minish->parsing.i_line])
	{
		i = 0;
		j = 0;
		if (check_pipe2(&line[minish->parsing.i_line], minish) == -1)
			return (-1);
		while (line[minish->parsing.i_line + i]
			&& line[minish->parsing.i_line + i] != '|')
		{
			i += pass_arg(&line[minish->parsing.i_line + i], minish);
			if (minish->parsing.error == 1)
				return (-1);
		}
		recup_pipe2(line, minish, i);
		minish->parsing.nb_pipe++;
		if (minish->parsing.error == 1)
			return (-1);
		if (line[minish->parsing.i_line] != '\0')
			minish->parsing.i_line++;
	}
	return (0);
}
