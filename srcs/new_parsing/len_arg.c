/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 06:38:09 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/18 22:58:17 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	brace_2(char *line, t_struct *minish)
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
	minish->parsing.len_arg += ft_strlen(tmp);
	return (1);
}

int	brace(char *line, t_struct *minish)
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
		return (brace_2(line, minish, i));
	return (1);
}

int	len_variable(char *line, t_struct *minish)
{
	int	i;

	i = 0;
	if (is_empty(line, minish) == 0)
	{
		while (line[i] && line[i] != ' ')
			i++;
		while (line[i] == ' ')
			i++;
		return (i - 1);
	}
	if (line[i] == '$' && (line[i + 1] == '\0' || line[i + 1] == ' '))
		minish->parsing.len_arg++;
	else
	{
		if (line[i] == '$' && line[i + 1] == '{')
			brace(line, minish);
		else if (line[i] == '$' && line[i] != '{')
			no_brace(line, minish);
	}
	while (line[i] && line[i] != 34 && line[i] != 39 && line[i] != '<'
		&& line[i] != '>' && line[i] != '$' && line[i] != '}')
		i++;
	return (i - 1);
}

// int	len_simple_quote(char *line, t_struct *minish)
// {
	
// }

// int	len_double_quotes(char *line, t_struct *minish)
// {
	
// }

int	len_arg(char *line, t_struct *minish)
{
	int i;

	i = 0;
	parsing->len_arg = 0;
	while(line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '$')
			i += len_variable(&line[i], parsing);
		// else if (line[i] == 39)
		// 	i += len_simple_quote(&line[i], parsing);
		// else if (line[i] == 34)
		// 	i += len_double_quotes(&line[i], parsing);
		// else if (line[i] == 60 || line[i] == 62)
		// 	i += pass_redirections(&line[i]);
		// else
		// 	i++;
		if (parsing->error == 1)
			return (-1);
		i++;
	}
	printf("len = %d\n", minish->parsing.len_arg);
	return (i);
}
