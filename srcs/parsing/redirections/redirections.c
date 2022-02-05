/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:59:13 by elisa             #+#    #+#             */
/*   Updated: 2022/02/02 14:01:08 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
