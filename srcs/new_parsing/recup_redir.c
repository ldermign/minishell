/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:18:37 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/01 23:08:22 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_redir(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			j++;
			while (line[i] == '<' || line[i] == '>' || line[i] == ' ')
				i++;
			while (line[i] && line[i] != '<' && line[i] != '>')
				i++;
		}
		else
			i++;
	}
	return (j);
}

char	*fill_redir(char *str, char *line, t_struct *minish)
{
	
}

char	*len_fill_redir(char *line, t_struct *minish)
{
	static int	i = 0;
	int			len;
	char		*str;

	len = len_redir(&line[i]);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
	{
		printf("ERROR MALLOC\n");
		minish->parsing.error = 1;
		return (NULL);
	}
	str = fill_redir(str, line, minish);
	return (str);
}

char	**recup_redir(char *line, t_struct *minish)
{
	char	**red;
	int		i;

	i = count_redir(line);
	red = malloc(sizeof(char *) * (i + 1));
	if (red == NULL)
	{
		minish->parsing.error = 1;
		printf("ERROR MALLOC\n");
		return (NULL);
	}
	red[i] = NULL;
	while (j < i)
	{
		red[j] = len_fill_redir(line, minish);
		if (red[j] == NULL)
			return (NULL);
		j++;
	}
	return (red);
}
