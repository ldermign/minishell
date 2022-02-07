/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_tst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:44:46 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/07 16:45:45 by ejahan           ###   ########.fr       */
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
	if (line[parsing->i_line] == ' ')
	{
		while (line[parsing->i_line] == ' ')
			parsing->i_line++;
		parsing->i_line--;
	}
	parsing->i_line--;
	if (str == NULL)
	{
		parsing->i_line++;
		return (0);
	}
	return (ft_strlen(str));
}

static int	simple_quote_echo(char *line, t_parsing *parsing)
{
	int	i;

	i = 0;
	parsing->i_line++;
	while (line[parsing->i_line] && line[parsing->i_line] != 39)
	{
		parsing->i_line++;
		i++;
	}
	if (line[parsing->i_line] == '\0')
	{
		printf("\033[0;31msyntax error :\033[0m echo : open quotes\n");
		parsing->error = 1;
		return (-1);
	}
	return (i);
}

static int	double_quotes_echo(char *line, t_parsing *parsing)
{
	int	i;

	i = 0;
	parsing->i_line++;
	while (line[parsing->i_line] && line[parsing->i_line] != 34)
	{
		if (line[parsing->i_line] == '$')
			i = i + check_variable(line, parsing);
		else
			i++;
		parsing->i_line++;
	}
	if (line[parsing->i_line] == '\0')
	{
		printf("\033[0;31msyntax error :\033[0m echo : open quotes\n");
		parsing->error = 1;
		return (-1);
	}
	return (i);
}

int	check_space(char *line, t_parsing *parsing)
{
	int	i;
	int	j;

	i = 0;
	while (line[parsing->i_line + i] == ' ')
		i++;
	if (line[parsing->i_line + i] == 60 || line[parsing->i_line + i] == 62)
		return (redirections(line, parsing));
	else if (line[parsing->i_line + i] == '$')
	{
		while (line[parsing->i_line] == ' ')
			parsing->i_line++;
		j = check_variable(line, parsing);
		if (line[parsing->i_line] != '<' && line[parsing->i_line] != '>'
			&& line[parsing->i_line] != '\0' && line[parsing->i_line] != '$')
			j++;
		return (j);
	}
	else if (line[parsing->i_line + i] == '\0')
	{
		parsing->i_line += i;
		return (0);
	}
	else
		return (1);
}

int	find_len(char *line, t_parsing *parsing)
{
	int	i;

	i = 0;
	while (line[parsing->i_line] && line[parsing->i_line] != '|')
	{
		if (line[parsing->i_line] == '$')
			i = i + check_variable(line, parsing);
		else if (line[parsing->i_line] == 39)
			i = i + simple_quote_echo(line, parsing);
		else if (line[parsing->i_line] == 34)
			i = i + double_quotes_echo(line, parsing);
		else if (line[parsing->i_line] == ' ')
			i = i + check_space(line, parsing);
		else if (line[parsing->i_line] == 60 || line[parsing->i_line] == 62)
			i += redirections(line, parsing);
		else
			i++;
		if (parsing->error == 1)
			return (-1);
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
	if (line[parsing->i_line] == ' ')
	{
		while (line[parsing->i_line] == ' ')
			parsing->i_line++;
		parsing->i_line--;
	}
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

int	len_variable(char *line, t_parsing *parsing)
{
	int		i;
	int		j;
	char	*str;
	char	var[ft_strlen(&line[parsing->i_line + 1]) + 1];

	i = 0;
	j = 1;
	while (line[parsing->i_line + j] && line[parsing->i_line + j] != ' '
		&& line[parsing->i_line + j] != 34 && line[parsing->i_line + j] != 39)
	{
		var[i] = line[parsing->i_line + j];
		i++;
		j++;
	}
	var[i] = '\0';
	str = getenv(var);
	if (str == NULL)
		return (0);
	return (ft_strlen(str));
}

int	fill_space(char *line, t_parsing *parsing, int i)
{
	int	j;
	int	k;

	j = 0;
	while (line[parsing->i_line + j] == ' ')
		j++;
	if (line[parsing->i_line + j] == 60 || line[parsing->i_line + j] == 62)
	{
		if (skip_redirections(line, parsing) == 1)
		{
			parsing->result[i] = ' ';
			return (1);
		}
		return (0);
	}
	else if (line[parsing->i_line + j] == '$')
	{
		while (line[parsing->i_line] == ' ')
			parsing->i_line++;
		k = len_variable(line, parsing);
		if (k != 0)
		{
			parsing->result[i] = ' ';
			return (1 + fill_variable(line, parsing, i + 1));
		}
		return (fill_variable(line, parsing, i));
	}
	else if (line[parsing->i_line + j] == '\0')
	{
		parsing->i_line += j;
		return (0);
	}
	else
		parsing->result[i] = ' ';
	return (1);
}

void	fill_result(char *line, t_parsing *parsing)
{
	int		i;

	i = 0;
	while (line[parsing->i_line] && line[parsing->i_line] != '|')
	{
		if (line[parsing->i_line] == '$')
			i = i + fill_variable(line, parsing, i);
		else if (line[parsing->i_line] == 39)
			i = i + fill_simple_quote(line, parsing, i);
		else if (line[parsing->i_line] == 34)
			i = i + fill_double_quotes(line, parsing, i);
		else if (line[parsing->i_line] == ' ')
			i = i + fill_space(line, parsing, i);
		else if (line[parsing->i_line] == 60 || line[parsing->i_line] == 62)
			skip_redirections(line, parsing);
		else
		{
			parsing->result[i] = line[parsing->i_line];
			i++;
		}
		parsing->i_line++;
	}
	parsing->result[i] = '\0';
}