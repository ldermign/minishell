/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 00:54:11 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/21 03:43:02 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	len_brace_2(char *line, t_struct *minish, int i)
// {
// 	char	*str;
// 	char	*tmp;

// 	str = malloc(sizeof(char) * i - 1);
// 	if (str == NULL)
// 		return (error_malloc(minish));
// 	str[i - 2] = '\0';
// 	i--;
// 	while (i > 1)
// 	{
// 		str[i - 2] = line[i];
// 		i--;
// 	}
// 	tmp = get_variable(&minish->env.env_ms, str);
// 	free(str);
// 	if (tmp == NULL)
// 		return (0);
// 	minish->parsing.len_arg += ft_strlen(tmp);
// 	return (1);
// }

// int	len_brace(char *line, t_struct *minish)
// {
// 	int		i;

// 	i = 2;
// 	while (is_variable_char(line[i]) == 0 && line[i] != '}')
// 		i++;
// 	if (is_variable_char(line[i]) == 1)
// 	{
// 		printf("${%c}: bad substitution\n", line[i]);
// 		minish->parsing.error = 1;
// 		return (-1);
// 	}
// 	if (line[i] == '}')
// 		return (len_brace_2(line, minish, i));
// 	return (1);
// }

int	len_brace(char *line, t_struct *minish)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 2;
	while (is_variable_char(line[i]) == 0 && line[i] != '}')
		i++;
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
	minish->parsing.len_arg += ft_strlen(tmp);
	return (1);
}

int	len_no_brace(char *line, t_struct *minish)
{
	int		i;
	int		j;
	char	*str;
	char	*tmp;

	i = 1;
	while (is_variable_char(line[i]) == 0 && line[i] != '}')
		i++;
	str = malloc(sizeof(char) * i - 1);
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
	if (tmp == NULL && is_variable_char(line[i]) == 1)
		return (0);
	minish->parsing.len_arg += ft_strlen(tmp);
	return (1);
}

int	len_variable2(char *line, t_struct *minish, int i)
{
	if (line[i] == '$' && line[i + 1] == '{')
	{
		len_brace(line, minish);
		while (line[i] && line[i] != '}')
			i++;
		i++;
	}
	else if (line[i] == '$' && line[i] != '{')
	{
		len_no_brace(line, minish);
		i++;
		while (line[i] && line[i] != 34 && line[i] != 39 && line[i] != '<'
			&& line[i] != '>' && line[i] != '$' && line[i] != '}'
			&& line[i] != ' ' && line[i] != '{')
			i++;
	}
	return (i);
}

// int	double_dollar(t_struct *minish)
// {
// 	minish->parsing.len_arg = ft_strlen(je sais pas -> numéro de processus de ton shell courant);
// 	return (1);
// }

int	len_variable(char *line, t_struct *minish)
{
	int	i;

	i = 0;
	if (is_empty(line, minish) == 0)
	{
		i++;
		while (line[i] && line[i] != ' ' && line[i] != 34 && line[i] != 39
			&& line[i] != '<' && line[i] != '>' && line[i] != '$'
			&& line[i] != '}' && line[i] != '{')
			i++;
		while (line[i] == ' ')
			i++;
		return (i - 1);
	}
	// if (line[i] == '$' && line[i + 1] == '$')
	// 	return (double_dollar(minish));
	if (line[i + 1] == 34 || line[i + 1] == 39)
		return (i);
	if (line[i] == '$' && (line[i + 1] == '\0' || line[i + 1] == ' '))
	{
		minish->parsing.len_arg++;
		return (1);
	}
	else
		i = len_variable2(line, minish, i);
	return (i - 1);
}
