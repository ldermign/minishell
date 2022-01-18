/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:18:15 by elisa             #+#    #+#             */
/*   Updated: 2022/01/13 00:36:05 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_variable(char *line, t_parsing *parsing)
{
	int		i;
	char	*str;
	char	var[ft_strlen(&line[parsing->i_line + 1]) + 1];

	i = 0;
	parsing->i_line++;
	while (line[parsing->i_line] && line[parsing->i_line] != ' '
		&& line[parsing->i_line] != 34 && line[parsing->i_line] != 39)
	{
		var[i] = line[parsing->i_line];
		i++;
		parsing->i_line++;
	}
	var[i] = '\0';
	str = getenv(var);
	parsing->i_line--;
	if (str == NULL)
		return (0);
	return (ft_strlen(str));
}

static int	simple_quote(char *line, t_parsing *parsing)
{
	int	i;

	i = 0;
	parsing->simple_quotes = 1;
	parsing->i_line++;
	while (line[parsing->i_line] && line[parsing->i_line] != 39)
	{
		parsing->i_line++;
		i++;
	}
	if (line[parsing->i_line] == '\0')
		return (-1);
	if (line[parsing->i_line] == 39)
		parsing->simple_quotes = 0;
	return (i);
}

static int	double_quotes(char *line, t_parsing *parsing)
{
	int	i;

	i = 0;
	parsing->double_quotes = 1;
	parsing->i_line++;
	while (line[parsing->i_line] && line[parsing->i_line] != 34)
	{
		if (line[parsing->i_line] == '$')
			i = i + check_variable(line, parsing);
		else
			i++;
		parsing->i_line++;
	}
	if (line[parsing->i_line] == 34)
		parsing->double_quotes = 0;
	return (i);
}

int	find_len(char *line, t_parsing *parsing)
{
	int	i;

	i = 0;
	while (line[parsing->i_line] && line[parsing->i_line] != '|'
		&& line[parsing->i_line] != 60 && line[parsing->i_line] != 62)
	{
		if (line[parsing->i_line] == '$')
			i = i + check_variable(line, parsing);
		else if (line[parsing->i_line] == 39)
			i = i + simple_quote(line, parsing);
		else if (line[parsing->i_line] == 34)
			i = i + double_quotes(line, parsing);
		else
			i++;
		if (parsing->simple_quotes != 0 || parsing->double_quotes != 0)
		{
			printf("\033[0;31msyntax error :\033[0m echo : open quotes\n");
			return (-1);
		}
		parsing->i_line++;
	}
	return (i);
}

int	fill_variable(char *line, t_parsing *parsing, int j)
{
	int		i;
	char	*str;
	char	var[ft_strlen(&line[parsing->i_line + 1]) + 1];

	i = 0;
	parsing->i_line++;
	while (line[parsing->i_line] && line[parsing->i_line] != ' '
		&& line[parsing->i_line] != 34 && line[parsing->i_line] != 39)
	{
		var[i] = line[parsing->i_line];
		i++;
		parsing->i_line++;
	}
	var[i] = '\0';
	str = getenv(var);
	parsing->i_line--;
	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		parsing->result[i + j] = str[i];
		i++;
	}
	return (ft_strlen(str));
}

int	fill_simple_quote(char *line, t_parsing *parsing, int i)
{
	int	j;

	j = 0;
	parsing->i_line++;
	while (line[parsing->i_line] && line[parsing->i_line] != 39)
	{
		parsing->result[i + j] = line[parsing->i_line];
		parsing->i_line++;
		j++;
	}
	return (j);
}

int	fill_double_quotes(char *line, t_parsing *parsing, int i)
{
	int	j;

	j = 0;
	parsing->i_line++;
	while (line[parsing->i_line] && line[parsing->i_line] != 34)
	{
		if (line[parsing->i_line] == '$')
			j = j + fill_variable(line, parsing, i + j);
		else
		{
			parsing->result[j + i] = line[parsing->i_line];
			j++;
		}
		parsing->i_line++;
	}
	return (j);
}

void	fill_result(char *line, t_parsing *parsing)
{
	int		i;

	i = 0;
	while (line[parsing->i_line] && line[parsing->i_line] != '|'
		&& line[parsing->i_line] != 60 && line[parsing->i_line] != 62)
	{
		if (line[parsing->i_line] == '$')
			i = i + fill_variable(line, parsing, i);
		else if (line[parsing->i_line] == 39)
			i = i + fill_simple_quote(line, parsing, i);
		else if (line[parsing->i_line] == 34)
			i = i + fill_double_quotes(line, parsing, i);
		else
		{
			parsing->result[i] = line[parsing->i_line];
			i++;
		}
		parsing->i_line++;
	}
	parsing->result[i] = '\0';
}