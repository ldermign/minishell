/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 00:35:39 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/29 18:43:54 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *str)
{
	static int	nbr_line = 0;
	char		*line;

	signal(SIGINT, handler_here_doc);
	line = readline("> ");
	if (line == NULL)
	{
		ctrl_d_hd(str, nbr_line);
		return ;
	}
	while (ft_strcmp(line, str) != 0 && g_sig_error != 42)
	{
		signal(SIGINT, handler_here_doc);
		free(line);
		line = readline("> ");
		nbr_line++;
		if (line == NULL)
		{
			ctrl_d_hd(str, nbr_line);
			return ;
		}
	}
	if (g_sig_error == 42)
		g_sig_error = 130;
	free(line);
}

t_list_hd	*recup_arg_here_doc(char *end, t_list_hd *hd)
{
	static int	nbr_line = 1;
	char		*line;
	char		*str;

	str = ft_strdup(end);
	free(hd->first->here_doc);
	delete_hd(hd);
	signal(SIGINT, handler_here_doc);
	line = readline("> ");
	if (line == NULL)
		return (ctrl_d(str, hd, nbr_line));
	while (ft_strcmp(line, str) != 0 && g_sig_error != 42)
	{
		signal(SIGINT, handler_here_doc);
		insertion_here_doc(hd, ft_strdup(line));
		line = readline("> ");
		nbr_line++;
		if (line == NULL)
			return (ctrl_d(str, hd, nbr_line));
	}
	if (g_sig_error == 42)
		g_sig_error = 130;
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
		fprintf(stderr, "ERROR MALLOC\n");
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
