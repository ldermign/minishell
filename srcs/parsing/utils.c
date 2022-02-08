/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:01:22 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/05 18:35:08 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	simple_quote(char *line, t_parsing *parsing)
{
	int	i;

	i = 0;
	parsing->i_line++;
	while (line[parsing->i_line] && line[parsing->i_line] != 39)
		parsing->i_line++;
	if (line[parsing->i_line] == '\0')
	{
		printf("\033[0;31msyntax error :\033[0m echo : open quotes\n");
		parsing->error = 1;
		return (-1);
	}
	return (i);
}

int	double_quotes(char *line, t_parsing *parsing)
{
	parsing->i_line++;
	while (line[parsing->i_line] && line[parsing->i_line] != 34)
		parsing->i_line++;
	if (line[parsing->i_line] == '\0')
	{
		printf("\033[0;31msyntax error :\033[0m echo : open quotes\n");
		parsing->error = 1;
		return (-1);
	}
	return (0);
}

int	check_quotes_and_redir(char *line, t_parsing *parsing)
{
	int	i;

	i = 0;
	while (line[parsing->i_line] && line[parsing->i_line] != '|')
	{
		if (line[parsing->i_line] == 39)
			simple_quote(line, parsing);
		else if (line[parsing->i_line] == 34)
			double_quotes(line, parsing);
		else if (line[parsing->i_line] == 60 || line[parsing->i_line] == 62)
			redirections(line, parsing);
		if (parsing->error == 1)
			return (-1);
		parsing->i_line++;
	}
	return (i);
}
