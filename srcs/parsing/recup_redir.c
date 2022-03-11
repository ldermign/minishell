/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:18:37 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/11 11:13:47 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *str)
{
	int		i;
	char	*line;
	char	*heredoc_eof;

	i = 2;
	while (str[i] == ' ')
		i++;
	heredoc_eof = &str[i];
	line = readline("> ");
	while (ft_strcmp(line, heredoc_eof) != 0)
			line = readline("> ");
}

int	norme_redir(char *line, t_struct *minish, int i)
{
	while (line[i] == '<' || line[i] == '>')
	{
		minish->parsing.len_arg++;
		i++;
	}
		i++;
	return (i);
}

int	len_redir(char *line, t_struct *minish)
{
	int	i;

	i = 0;
	minish->parsing.len_arg = 1;
	i += norme_redir(line, minish, i);
	while (line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>')
	{
		if (line[i] == '$')
			i += len_variable(&line[i], minish);
		else if (line[i] == 39)
			i += len_simple_quote(&line[i], minish);
		else if (line[i] == 34)
			i += len_double_quotes(&line[i], minish);
		else
			minish->parsing.len_arg++;
		if (minish->parsing.error != 0)
			return (-1);
		i++;
	}
	while (line[i] && line[i] != '<' && line[i] != '>')
		i++;
	return (i);
}

char	*fill_redir(char *str, char *line, t_struct *minish, int i)
{
	minish->parsing.fill_arg = 0;
	while (line[i] == '<' || line[i] == '>')
	{
		str[minish->parsing.fill_arg++] = line[i];
		i++;
	}
	while (line[i] == ' ')
		i++;
	str[minish->parsing.fill_arg++] = ' ';
	while (line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>')
	{
		if (line[i] == '$')
			i += fill_variable(&line[i], str, minish);
		else if (line[i] == 39)
			i += fill_simple_quote(&line[i], str, minish);
		else if (line[i] == 34)
			i += fill_double_quotes(&line[i], str, minish);
		else
			str[minish->parsing.fill_arg++] = line[i];
		if (minish->parsing.error != 0)
			return (NULL);
		i++;
	}
	str[minish->parsing.fill_arg] = '\0';
	return (str);
}

char	*len_fill_redir(char *line, t_struct *minish)
{
	static int	i = 0;
	int			j;
	char		*str;

	while (line[i] && line[i] != '<' && line[i] != '>')
		i++;
	j = len_redir(&line[i], minish);
	str = malloc(sizeof(char) * (minish->parsing.len_arg + 1));
	if (str == NULL)
	{
		printf("ERROR MALLOC\n");
		minish->parsing.error = 1;
		return (NULL);
	}
	str = fill_redir(str, &line[i], minish, 0);
	i += j;
	if (line[i] == '\0')
		i = 0;
	return (str);
}

char	**recup_redir(char *line, t_struct *minish)
{
	char	**red;
	int		i;
	int		j;

	j = 0;
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
