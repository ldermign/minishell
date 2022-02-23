/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 21:45:54 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/23 00:36:28 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_redir(char *line, t_struct *minish)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * minish->parsing.len_arg + 1);
	if (str == NULL)
		return (NULL);
	minish->parsing.fill_arg = 0;
	while (line[i] && line[i] != ' ' && line[i] != '<'
		&& line[i] != '>' && line[i])
	{
		if (line[i] == '$')
			i += fill_variable(&line[i], str, minish);
		else if (line[i] == 39)
			i += fill_simple_quote(&line[i], str, minish);
		else if (line[i] == 34)
			i += fill_double_quotes(&line[i], str, minish);
		else
			str[minish->parsing.fill_arg++] = line[i];
		if (minish->parsing.error == 1)
			return (-1);
		i++;
	}
	str[minish->parsing.fill_arg] = '\0';
	return (str);
}

int	len_redir(char *line, t_struct *minish)
{
	int	i;

	i = 0;
	minish->parsing.len_arg = 0;
	while (line[i] && line[i] != '<' && line[i] != '>' && line[i] != ' ')
	{
		if (line[i] == '$')
			i += len_variable(&line[i], minish);
		else if (line[i] == 39)
			i += len_simple_quote(&line[i], minish);
		else if (line[i] == 34)
			i += len_double_quotes(&line[i], minish);
		else
			minish->parsing.len_arg++;
		if (minish->parsing.error == 1)
			return (-1);
		i++;
	}
	return (i);
}

int	count_redir(char *line, t_struct *minish)
{
	int	i;

	i = 1;
	if (line[i] == line[0])
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|' || line[i] == '<' || line[i] == '>' || line[i] == '\0')
	{
		if (line[i] == '\0')
			printf("syntax error near unexpected token `newline'\n");
		else
			printf("syntax error near unexpected token `%c'\n", line[i]);
		minish->parsing.error = 1;
		return (-1);
	}
	minish->parsing.nb_redir++;
	while (line[i] && line[i] != '<' && line[i] != '>')
		i++;
	return (i);
}

int	recup_redir(t_args *arg, t_struct *minish)
{
	int	i;
	int	j;

	i = 0;
	minish->parsing.nb_redir = 0;
	while (&arg->command[i])
		i += count_redir(&arg->command[i], minish);
	j = minish->parsing.nb_redir;
	minish->args->first->redir = malloc(sizeof(char *) * j + 1);
	if (minish->args->first->redir == NULL)
		return (error_malloc(minish));
	arg->redir[j] = NULL;
	j = 0;
	while (&arg->command[i])
	{
		len_redir(&arg->command[i]);
		arg->redir[j] = fill_redir(&arg->command[i], minish);
		if (arg->redir[j] == NULL)
			return (error_malloc(minish));
		j++;
	}
	return (i);
}

/*

count arg -> pass_redir + check si probleme + count_redir++
malloc redir * count_redir + 1
len arg -> quand pass_redir -> count len redir + fill redir

*/
