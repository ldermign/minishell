/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:18:15 by elisa             #+#    #+#             */
/*   Updated: 2022/02/02 15:41:10 by elisa            ###   ########.fr       */
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

static int	double_quotes(char *line, t_parsing *parsing)
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

// 	60 <	62 >

void	first_redir_echo(char *line, t_parsing *parsing)	// < 
{
	char	str[ft_strlen(&line[parsing->i_line + 1])];
	int		i;
	int		fd;

	i = 0;
	parsing->i_line++;
	while (line[parsing->i_line] == ' ')
		parsing->i_line++;
	while (line[parsing->i_line] && line[parsing->i_line] != ' ')
	{
		str[i] = line[parsing->i_line];
		i++;
		parsing->i_line++;
	}
	str[i] = '\0';
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		printf("error : %s: no such file or directory\n", str);
		parsing->error = 1;
		return ;
	}
	close(fd);	
	while (line[parsing->i_line] == ' ')
		parsing->i_line++;
	parsing->i_line--;
}

// void	second_redir_echo(char *line, t_parsing *parsing)	// << 
// {
	
// }

// void	third_redir_echo(char *line, t_parsing *parsing)	// > 
// {
// 	parsing->i_line++;
// 	while (line[parsing->i_line] == ' ')
// 		parsing->i_line++;
// 	// flemme
// }

// void	fourth_redir_echo(char *line, t_parsing *parsing)	// >> 
// {
// }

void	redirections_echo(char *line, t_parsing *parsing)
{
	// skip_redirections(line, parsing); // tmp
	if (line[parsing->i_line] == 60 && line[parsing->i_line + 1] != 60)
		first_redir_echo(line, parsing);
// 	if (line[parsing->i_line] == 60 && line[parsing->i_line + 1] == 60)
// 		second_redir_echo(line, parsing);
// 	if (line[parsing->i_line] == 62 && line[parsing->i_line + 1] != 62)
// 		third_redir_echo(line, parsing);
// 	if (line[parsing->i_line] == 62 && line[parsing->i_line + 1] == 62)
// 		fourth_redir_echo(line, parsing);
}

int	find_len(char *line, t_parsing *parsing)
{
	int	i;

	i = 0;
	while (line[parsing->i_line] && line[parsing->i_line] != '|')
		// && line[parsing->i_line] != 60 && line[parsing->i_line] != 62)
	{
		if (line[parsing->i_line] == '$')
			i = i + check_variable(line, parsing);
		else if (line[parsing->i_line] == 39)
			i = i + simple_quote(line, parsing);
		else if (line[parsing->i_line] == 34)
			i = i + double_quotes(line, parsing);
		else if (line[parsing->i_line] == 60 || line[parsing->i_line] == 62)
			redirections_echo(line, parsing);
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

void	skip_redirections(char *line, t_parsing *parsing)
{
	while (line[parsing->i_line] == 60 || line[parsing->i_line] == 62
		|| line[parsing->i_line] == ' ')
		parsing->i_line++;
	if (line[parsing->i_line] == 34 || line[parsing->i_line] == 39)
	{
		parsing->i_line++;
		while (line[parsing->i_line] != 34 && line[parsing->i_line] != 39)
			parsing->i_line++;
		parsing->i_line++;
	}
	else
	{
		while (line[parsing->i_line] != ' ')
			parsing->i_line++;
	}
	while (line[parsing->i_line] == ' ')
		parsing->i_line++;
	parsing->i_line--;
}

void	fill_result(char *line, t_parsing *parsing)
{
	int		i;

	i = 0;
	while (line[parsing->i_line] && line[parsing->i_line] != '|')
		// && line[parsing->i_line] != 60 && line[parsing->i_line] != 62)
	{
		if (line[parsing->i_line] == '$')
			i = i + fill_variable(line, parsing, i);
		else if (line[parsing->i_line] == 39)
			i = i + fill_simple_quote(line, parsing, i);
		else if (line[parsing->i_line] == 34)
			i = i + fill_double_quotes(line, parsing, i);
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

// echo ><
// bash: syntax error near unexpected token `<'

// echo > "hgv b$PWD"
// bash: hgv b/Users/elisa/Desktop: No such file or directory

// echo > "$PW D"
//  ls
//  D	42	minishell	minishell_test	push_swap	sujets

// echo > "$PWD"
// bash: /Users/elisa/Desktop: Is a directory

// > && >>
// des que nouvelle redirection -> creation fichier
// 		mais ecrit seulement dans le dernier

// < 
// check si le fichier existe mais fait rien

// <<
// check jusque == a STOP (ou autre)
// si plusieur dans line, prend que le dernier en compte
