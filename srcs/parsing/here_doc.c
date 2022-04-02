/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 00:35:39 by ejahan            #+#    #+#             */
/*   Updated: 2022/04/02 15:33:57 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *str, t_struct *minish)
{
	char		*line;

	line = readline("> ");
	signal(SIGINT, SIG_IGN);
	if (line == NULL)
	{
		ctrl_d_hd(str, minish->nbr_line);
		return ;
	}
	while (ft_strcmp(line, str) != 0)
	{
		free(line);
		line = readline("> ");
		minish->nbr_line++;
		if (line == NULL)
		{
			ctrl_d_hd(str, minish->nbr_line);
			return ;
		}
	}
	free(line);
}

t_list_hd	*recup_arg_here_doc(char *end, t_list_hd *hd, t_struct *minish)
{
	char		*line;
	char		*str;

	signal(SIGINT, SIG_IGN);
	str = ft_strdup(end);
	free(hd->first->here_doc);
	delete_hd(hd);
	line = readline("> ");
	if (line == NULL)
		return (ctrl_d(str, hd, minish->nbr_line));
	while (ft_strcmp(line, str) != 0)
	{
		insertion_here_doc(hd, get_var_hd(line, minish));
		line = readline("> ");
		minish->nbr_line++;
		if (line == NULL)
			return (ctrl_d(str, hd, minish->nbr_line));
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
	str = fill_hd(line);
	if (str == NULL)
	{
		fprintf(stderr, "ERROR MALLOC\n");
		minish->parsing.error = 1;
		return (NULL);
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
						arg->first->here_doc, ms);
				arg->first->here_doc = reverse_list_hd(arg->first->here_doc);
				arg->first->args_here_doc = arg_list(arg->first->here_doc, ms);
				break ;
			}
			else
				here_doc(arg->first->here_doc->first->here_doc, ms);
			free(arg->first->here_doc->first->here_doc);
			delete_hd(arg->first->here_doc);
		}
		arg->first = arg->first->next;
	}
	arg->first = tmp;
}
