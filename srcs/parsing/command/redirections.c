/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:59:13 by elisa             #+#    #+#             */
/*   Updated: 2022/02/04 11:44:35 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 	60 <	62 >

// int	check_error_red(char *line, t_parsing *parsing)
// {
//     // flemme la j'avoue
// }

void	first_redir(char *line, t_parsing *parsing)	// < 
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

int	check_end(char *end, char *new_line)
{
	// printf("TEST %s, %s\n", end, new_line);
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
	// ft_memcmp(end, newline, len_end + 1); //pk ca marche paaaaaaaas
	return (0);
	// return (-1);
}

void	second_redir(char *line, t_parsing *parsing)	// << 
{
	char	*end;
	char	*new_line;
	int		i;

	i = 0;
	parsing->i_line += 2;
	while (line[parsing->i_line] == ' ')
		parsing->i_line++;
	while (line[parsing->i_line + i] != ' ')
		i++;
	end = malloc(sizeof(char) * i + 1);
	if (end == NULL)
	{
		printf("error malloc\n");
		parsing->error = 1;
		return ;
	}
	i = 0;
	while (line[parsing->i_line] && line[parsing->i_line] != ' ')
	{
		end[i] = line[parsing->i_line];
		parsing->i_line++;
		i++;
	}
	end[i] = '\0';
	printf("[%s]\n", end);
	while (42)
	{
		new_line = readline("> ");
		if (check_end(end, new_line) == 0)
		{
			printf("test\n");
			free(end);
			printf("test\n");
			free(new_line);
			printf("test\n");
			return ;
		}
		free(new_line);
	}
	free(end);
}

// void	third_redir(char *line, t_parsing *parsing)	// > 
// {
// 	parsing->i_line++;
// 	while (line[parsing->i_line] == ' ')
// 		parsing->i_line++;
// 	// flemme
// }

// void	fourth_redir(char *line, t_parsing *parsing)	// >> 
// {
// }

void	redirections(char *line, t_parsing *parsing)
{
	// if (check_error_red(line, parsing) == -1)
	// {
	// 	parsing->error = 1;
	// 	return ;
	// }
	if (line[parsing->i_line] == 60 && line[parsing->i_line + 1] != 60)
		first_redir(line, parsing);
	if (line[parsing->i_line] == 60 && line[parsing->i_line + 1] == 60)
		second_redir(line, parsing);
// 	if (line[parsing->i_line] == 62 && line[parsing->i_line + 1] != 62)
// 		third_redir(line, parsing);
// 	if (line[parsing->i_line] == 62 && line[parsing->i_line + 1] == 62)
// 		fourth_redir(line, parsing);
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
