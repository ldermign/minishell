/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 05:51:31 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/23 10:23:55 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty_brace2(char *line, t_struct *minish, int i)
{
	char	*str;
	char	*tmp;

	str = malloc(sizeof(char) * i - 1);
	if (str == NULL)
		return (error_malloc(minish));
	str[i - 2] = '\0';
	i--;
	while (i > 1)
	{
		str[i - 2] = line[i];
		i--;
	}
	tmp = get_variable(&minish->env.env_ms, str);
	free(str);
	if (tmp == NULL)
		return (0);
	return (1);
}

int	is_empty_brace(char *line, t_struct *minish)
{
	int		i;

	i = 2;
	while (is_variable_char(line[i]) == 0 && line[i] != '}')
		i++;
	if (is_variable_char(line[i]) == 1)
	{
		printf("${%c}: bad substitution\n", line[i]);
		minish->parsing.error = 1;
		return (-1);
	}
	if (line[i] == '}' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
		return (is_empty_brace2(line, minish, i));
	return (1);
}

int	is_empty_no_brace(char *line, t_struct *minish)
{
	int		i;
	int		j;
	char	*str;
	char	*tmp;

	i = 1;
	while (is_variable_char(line[i]) == 0 && line[i] != '}')
		i++;
	// printf("i = %d\n", i);
	str = malloc(sizeof(char) * i);
	if (str == NULL)
		return (error_malloc(minish));
	j = i;
	str[i - 1] = '\0';
	i--;
	while (i > 0)
	{
		str[i - 1] = line[i];
		i--;
	}
	tmp = get_variable(&minish->env.env_ms, str);
	free(str);
	if (tmp == NULL && (line[j] == ' ' || line[j] == '\0'))
		return (0);
	return (1);
}

int	is_empty(char *line, t_struct *minish)
{
	int		i;

	i = 0;
	if (line[i] == '$' && (line[i + 1] == '\0' || line[i + 1] == ' '))
		return (1);
	if (line[i + 1] == 34 || line[i + 1] == 39)
		return (1);
	if (line[i] == '$' && line[i + 1] == '{')
		return (is_empty_brace(line, minish));
	else if (line[i] == '$' && line[i] != '{')
		return (is_empty_no_brace(line, minish));
	return (1);
}
