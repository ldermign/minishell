/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:40:44 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/31 14:52:41 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_hd(char *str, char c, int *i)
{
	int	j;

	j = 0;
	(*i)++;
	while (str[*i] && str[*i] != c)
	{
		j++;
		(*i)++;
	}
	if (str[*i] != '\0')
		(*i)++;
	return (j);
}

int	len_hd(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == 34 || str[i] == 39)
			j += quotes_hd(str, str[i], &i);
		else
		{
			j++;
			i++;
		}
	}
	return (j);
}

int	fill_quotes_hd(char *line, int *j, int *i, char *str)
{
	char	c;

	c = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != c)
	{
		str[*j] = line[*i];
		(*j)++;
		(*i)++;
	}
	if (line[*i] != '\0')
		(*i)++;
	return (*j);
}

char	*fill_hd(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (len_hd(line) + 1));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, len_hd(line) + 1);
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == 34 || line[i] == 39)
			fill_quotes_hd(line, &j, &i, str);
		else
		{
			str[j] = line[i];
			j++;
			i++;
		}
	}
	return (str);
}
