/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_variable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 04:30:23 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/19 14:25:21 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_brace(char *line, char *arg, t_struct *minish)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 2;
	while (is_variable_char(line[i]) == 0 && line[i] != '}')
		i++;
	str = malloc(sizeof(char) * (i - 1));
	if (str == NULL)
		return (error_malloc(minish));
	str[i - 2] = '\0';
	i--;
	while (i > 1)
	{
		str[i - 2] = line[i];
		i--;
	}
	tmp = get_variable(minish->env.env_ms, str);
	free(str);
	if (tmp == NULL)
		return (0);
	i = 0;
	while (tmp[i])
		arg[minish->parsing.fill_arg++] = tmp[i++];
	return (1);
}

int	fill_no_brace(char *line, char *arg, t_struct *minish, int i)
{
	int		j;
	char	*str;
	char	*tmp;

	while (is_variable_char(line[i]) == 0 && line[i] != '}')
		i++;
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
	tmp = get_variable(minish->env.env_ms, str);
	free(str);
	if (tmp == NULL && is_variable_char(line[j]) == 1)
		return (0);
	i = 0;
	while (tmp[i])
		arg[minish->parsing.fill_arg++] = tmp[i++];
	return (1);
}

int	fill_variable2(char *line, char *str, t_struct *minish, int i)
{
	if (line[i] == '$' && line[i + 1] == '{')
	{
		fill_brace(line, str, minish);
		while (line[i] && line[i] != '}')
			i++;
		i++;
	}
	else if (line[i] == '$' && line[i] != '{')
	{
		fill_no_brace(line, str, minish, 1);
		i++;
		while (line[i] && line[i] != 34 && line[i] != 39 && line[i] != '<'
			&& line[i] != '>' && line[i] != '$' && line[i] != '}'
			&& line[i] != ' ' && line[i] != '{')
			i++;
	}
	return (i);
}

int	fill_variable(char *line, char *str, t_struct *minish)
{
	int	i;

	i = 0;
	if (line[i] == '$' && line[i + 1] == '?')
		return (fill_sig_error(minish, str));
	if (is_empty(line, minish) == 0)
		return (if_is_empty(line, i));
	if (line[i] == '$' && line[i + 1] == '$')
		return (fill_double_dollar(minish, str));
	if (line[i] == '$' && (line[i + 1] == '\0' || line[i + 1] == ' '
			|| (line[i + 1] == 34 && minish->parsing.quotes == 1)))
	{
		str[minish->parsing.fill_arg++] = line[i];
		return (0);
	}
	else
		i = fill_variable2(line, str, minish, i);
	return (i - 1);
}
