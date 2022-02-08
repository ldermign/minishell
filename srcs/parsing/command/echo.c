/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:44:46 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/08 14:27:19 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_variable_crochet(char *line, t_parsing *parsing)
{
	int		i;
	char	*str;
	char	var[ft_strlen(&line[parsing->i_line + 1]) + 1];

	i = 0;
	parsing->i_line++;
	while (line[parsing->i_line] && line[parsing->i_line] != ' '
		&& line[parsing->i_line] != 34 && line[parsing->i_line] != 39
		&& line[parsing->i_line] != '|' && line[parsing->i_line] != '$'
		&& line[parsing->i_line] != '}')
	{
		var[i] = line[parsing->i_line];
		i++;
		parsing->i_line++;
	}
	var[i] = '\0';
	str = getenv(var);
	if (line[parsing->i_line] == ' ' || line[parsing->i_line] == 34
		|| line[parsing->i_line] == 39 || line[parsing->i_line] == '|'
		|| line[parsing->i_line] != '$')
	{
		printf("${%s}: bad substitution\n", str);
		parsing->error = 1;
		return (-1);
	}
	if (line[parsing->i_line] == '\0')
	{
		printf("error : open crochet (jsp comment on dit faudra changer\n)");
		parsing->error = 1;
		return (-1);
	}
	if (line[parsing->i_line] == '}')
		parsing->i_line++;
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

static int	check_variable(char *line, t_parsing *parsing)
{
	int		i;
	char	*str;
	char	var[ft_strlen(&line[parsing->i_line + 1]) + 1];

	i = 0;
	parsing->i_line++;
	if (line[parsing->i_line] == '{')
		return (check_variable_crochet(line, parsing));
	while (line[parsing->i_line] && line[parsing->i_line] != ' '
		&& line[parsing->i_line] != 34 && line[parsing->i_line] != 39
		&& line[parsing->i_line] != '|' && line[parsing->i_line] != '$'
		&& line[parsing->i_line] != '}')
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
			&& line[parsing->i_line] != '\0' && line[parsing->i_line] != '$'
			&& line[parsing->i_line] != '|')
			j++;
		return (j);
	}
	else if (line[parsing->i_line + i] == '\0' || line[parsing->i_line + i] == '|')
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
