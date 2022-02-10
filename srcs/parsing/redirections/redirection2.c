/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:59:13 by elisa             #+#    #+#             */
/*   Updated: 2022/02/10 19:53:42 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// << 

int	check_end(char *end, char *new_line)
{
	unsigned int	len_end;
	int				i;

	len_end = ft_strlen(end);
	i = 0;
	if (ft_strlen(new_line) == len_end)
	{
		while (i < (int)len_end)
		{
			if (end[i] != new_line[i])
				return (end[i] - new_line[i]);
			i++;
		}
	}
	else
		return (-1);
	return (0);
}

void	parse_second_redir(char *line, t_parsing *parsing)
{
	parsing->i_line += 2;
	while (line[parsing->i_line] == ' ')
		parsing->i_line++;
	while (line[parsing->i_line] && line[parsing->i_line] != ' '
		&& line[parsing->i_line] != 60 && line[parsing->i_line] != 62
		&& line[parsing->i_line] != '|')
	{
		if (line[parsing->i_line] == 39)
			simple_quote(line, parsing);
		else if (line[parsing->i_line] == 34)
			double_quotes(line, parsing);
		if (parsing->error == 1)
			return ;
		parsing->i_line++;
	}
}

// void	second_redir(char *line, t_parsing *parsing)	// << 
// {
// 	char	*end;
// 	char	*new_line;
// 	int		i;

// 	i = 0;
// 	parsing->i_line += 2;
// 	while (line[parsing->i_line] == ' ')
// 		parsing->i_line++;
// 	while (line[parsing->i_line + i] != ' ')
// 		i++;
// 	end = malloc(sizeof(char) * i + 1);
// 	if (end == NULL)
// 	{
// 		printf("error malloc\n");
// 		parsing->error = 1;
// 		return ;
// 	}
// 	i = 0;
// 	while (line[parsing->i_line] && line[parsing->i_line] != ' ')
// 	{
// 		end[i] = line[parsing->i_line];
// 		parsing->i_line++;
// 		i++;
// 	}
// 	end[i] = '\0';
// 	while (42)
// 	{
// 		new_line = readline("> ");
// 		if (check_end(end, new_line) == 0)
// 		{
// 			free(end);
// 			free(new_line);
// 			return ;
// 		}
// 		free(new_line);
// 	}
// 	free(end);
// }
