/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 00:35:39 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/12 08:29:15 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *str)
{
	char	*line;

	line = readline("> ");
	if (line == NULL)
	{
		rl_on_new_line();
		return ;
	}
	while (ft_strcmp(line, str) != 0)
	{
		line = readline("> ");
		if (line == NULL)
		{
			rl_on_new_line();
			return ;
		}
		free(line);
	}
	free(line);
}

t_list_hd	*recup_arg_here_doc(char *str, t_list_hd *hd)
{
	char	*line;

	delete_hd(hd);
	line = readline("> ");
	if (line == NULL)
	{
		rl_on_new_line();
		return (hd);
	}
	while (ft_strcmp(line, str) != 0)
	{
		printf("la\n");
		insertion_here_doc(hd, line);
		line = readline("> ");
		if (line == NULL)
		{
			rl_on_new_line();
			return (hd);
		}
	}
	free(line);
	return (hd);
}

t_struct	*recup_here_doc_end(char *line, t_struct *minish)
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

	tmp = args->first;
	while (args->first != NULL)
	{
		args->first->here_doc = reverse_list_hd(args->first->here_doc);
		while (args->first->here_doc->first != NULL)
		{
			if (args->first->here_doc->first->next == NULL)
			{
				args->first->here_doc = recup_arg_here_doc(args->first->here_doc->first->here_doc, args->first->here_doc);
				args->first->here_doc = reverse_list_hd(args->first->here_doc);
				break ;
			}
			else
				here_doc(args->first->here_doc->first->here_doc);
			delete_hd(args->first->here_doc);
		}
		args->first = args->first->next;
		// free(args->first->here_doc->first);
		// free(args->first->here_doc);
	}
	args->first = tmp;
}
