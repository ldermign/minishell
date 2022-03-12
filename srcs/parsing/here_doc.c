/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 00:35:39 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/12 07:52:54 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *str)
{
	int		i;
	char	*line;
	char	*heredoc_eof;

	i = 0;
	while (str[i] == ' ')
		i++;
	heredoc_eof = &str[i];
	line = readline("> ");
	while (ft_strcmp(line, heredoc_eof) != 0)
			line = readline("> ");
}

t_struct	*recup_here_doc(char *line, t_struct *minish)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
	{
		printf("ERROR MALLOC\n");
		minish->parsing.error = 1;
		return (NULL);
	}
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i] = line[i];
		i--;
	}
	insertion_here_doc(minish->args->first->here_doc, str);
	return (minish);
}

void	exec_here_doc(t_list_arg *args)
{
	t_args		*tmp;
	t_here_doc	*re_tmp;

	tmp = args->first;
	re_tmp = args->first->here_doc->first;
	while (args->first != NULL)
	{
		args->first->here_doc = reverse_list_hd(args->first->here_doc);
		re_tmp = args->first->here_doc->first;
		while (args->first->here_doc->first != NULL)
		{
			if (args->first->here_doc->first->next == NULL)
			{
				here_doc(args->first->here_doc->first->here_doc);
				// here_doc + recup
			}
			else
				here_doc(args->first->here_doc->first->here_doc);
			// args->first->here_doc->first = args->first->here_doc->first->next;
			delete_hd(args->first->here_doc);
		}
		args->first = args->first->next;
		// free(args->first->here_doc->first);
		// free(args->first->here_doc);
		// args->first->here_doc->first = re_tmp;
	}
	args->first = tmp;
}
