/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 00:35:39 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/20 22:06:26 by ejahan           ###   ########.fr       */
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
		free(line);
		line = readline("> ");
		if (line == NULL)
		{
			rl_on_new_line();
			return ;
		}
	}
	free(line);
}

t_list_hd	*recup_arg_here_doc(char *end, t_list_hd *hd)
{
	char	*line;
	char	*str;

	str = ft_strdup(end);
	free(hd->first->here_doc);
	delete_hd(hd);
	line = readline("> ");
	if (line == NULL)
	{
		free(str);
		rl_on_new_line();
		return (hd);
	}
	while (ft_strcmp(line, str) != 0)
	{
		insertion_here_doc(hd, ft_strdup(line));
		line = readline("> ");
		if (line == NULL)
		{
			free(str);
			rl_on_new_line();
			return (hd);
		}
	}
	free(str);
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

void	exec_here_doc(t_list_arg *arg, t_struct *ms)
{
	t_args		*tmp;

	tmp = arg->first;
	while (arg->first != NULL)
	{
		arg->first->here_doc = reverse_list_hd(arg->first->here_doc);
		while (arg->first->here_doc->first != NULL)
		{
			if (arg->first->here_doc->first->next == NULL)
			{
				arg->first->here_doc
					= recup_arg_here_doc(arg->first->here_doc->first->here_doc,
						arg->first->here_doc);
				arg->first->here_doc = reverse_list_hd(arg->first->here_doc);
				arg->first->args_here_doc = arg_list(arg->first->here_doc, ms);
				break ;
			}
			else
				here_doc(arg->first->here_doc->first->here_doc);
			free(arg->first->here_doc->first->here_doc);
			delete_hd(arg->first->here_doc);
		}
		arg->first = arg->first->next;
	}
	arg->first = tmp;
}
