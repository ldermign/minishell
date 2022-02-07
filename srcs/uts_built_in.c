/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:54:48 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/07 14:02:25 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_variable(char *prompt)
{
	int	i;
	int	ret;
	int	len;

	i = 0;
	ret = 0;
	len = 0;
	while (prompt[i] == ' ')
		i++;
	i += 6;
	while (prompt[i] == ' ')
		i++;
	while (prompt[i] != '=')
	{
		len++;
		i++;
	}
	i++;
	len++;
	if (prompt[i] == '"')
	{
		i++;
		ret = 1;
	}
	while ((ret == 1 && prompt[i] != '"') || (ret == 0 && prompt[i] != ' '))
	{
		i++;
		len++;
	}
	return (len);
}

int	light_parse_export(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] == ' ')
		i++;
	i += 6;
	while (prompt[i] == ' ')
		i++;
	if (prompt[i] != '=')
		return (EXIT_FAILURE);
	i++;
	if (prompt[i] == '&' || prompt[i] == '(' || prompt[i] == ')' || prompt[i] == ';' || prompt[i] == '<' || prompt[i] == '>' || prompt[i] == '|') // pas vraiment, checker commant il fonctionnne
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	light_parse_echo(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	i += 4;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] && str[i] == ' ')
		{
			while (str[i] && str[i] == ' ')
				i++;
			return (i);
		}
	}
	return (-1);
}

char	*create_path(char *path, char *cmd)
{
	size_t	i;
	int		j;
	char	*dst;

	if (path == NULL || cmd == NULL)
		return (NULL);
	i = 0;
	j = 0;
	dst = malloc(sizeof(char) * ft_strlen(path) + ft_strlen(cmd) + 2);
	if (dst == NULL)
		return (NULL);
	while (i < ft_strlen(path))
	{
		dst[i] = path[i];
		i++;
	}
	dst[i++] = '/';
	while (i < ft_strlen(path) + ft_strlen(cmd) + 1)
	{
		dst[i] = cmd[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*get_good_variable(char *prompt, int size)
{
	int		i;
	int		j;
	int		ret;
	char	*str;

	i = 0;
	j = 0;
	ret = 0;
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
	{
		printf("Bad malloc.\n");
		return (NULL);
	}
	while (prompt[i] == ' ')
		i++;
	i += 6;
	while (prompt[i] == ' ')
		i++;
	while (j < size)
	{
		str[j] = prompt[i];
		if (ret == 0 && prompt[i] == '=' && prompt[i + 1] == '"')
		{
			i++;
			ret = 1;
		}
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}
