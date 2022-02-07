/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_tst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:59:13 by elisa             #+#    #+#             */
/*   Updated: 2022/02/07 16:43:07 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 	60 <	62 >

// liste a completer 

int	check_error_red(char *line, t_parsing *parsing)
{
	parsing->i_line++;
	if (line[parsing->i_line] == line[parsing->i_line - 1])
		parsing->i_line++;
	if (line[parsing->i_line] == '<' || line[parsing->i_line] == '>'
		|| line[parsing->i_line] == '\n' || line[parsing->i_line] == '*'
		|| line[parsing->i_line] == ';' || line[parsing->i_line] == '('
		|| line[parsing->i_line] == ')' || line[parsing->i_line] == '`')
	{
		printf("syntax error near unexpected token `");
		printf("%c'\n", line[parsing->i_line]);
		parsing->error = 1;
		return (-1);
	}
	if (line[parsing->i_line - 1] == line[parsing->i_line - 2])
		parsing->i_line--;
	parsing->i_line--;
	return (0);
}

int	redirections(char *line, t_parsing *parsing)
{
	while (line[parsing->i_line] == ' ')
		parsing->i_line++;
	if (check_error_red(line, parsing) == -1)
	{
		parsing->error = 1;
		return (-1);
	}
	while (line[parsing->i_line] == ' ')
		parsing->i_line++;
	if (line[parsing->i_line] == 60 && line[parsing->i_line + 1] != 60)
		parse_first_redir(line, parsing);
	else if (line[parsing->i_line] == 60 && line[parsing->i_line + 1] == 60)
		parse_second_redir(line, parsing);
	else if (line[parsing->i_line] == 62 && line[parsing->i_line + 1] != 62)
		parse_third_redir(line, parsing);
	else if (line[parsing->i_line] == 62 && line[parsing->i_line + 1] == 62)
		parse_fourth_redir(line, parsing);
	while (line[parsing->i_line] == ' ')
		parsing->i_line++;
	parsing->i_line--;
	if (line[parsing->i_line] != '<' && line[parsing->i_line] != '>'
		&& line[parsing->i_line] != '\0' && line[parsing->i_line] != '$')
		return (1);
	return (0);
}

int	skip_redirections(char *line, t_parsing *parsing)
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
		while (line[parsing->i_line] && line[parsing->i_line] != ' ')
			parsing->i_line++;
	}
	while (line[parsing->i_line] == ' ')
		parsing->i_line++;
	if (line[parsing->i_line] != '<' && line[parsing->i_line] != '>'
		&& line[parsing->i_line] != '\0' && line[parsing->i_line] != '$')
	{
		parsing->i_line--;
		return (1);
	}
	parsing->i_line--;
	return (0);
}

// bash-5.0$ echo ugvj >
// bash: syntax error near unexpected token `newline'

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
