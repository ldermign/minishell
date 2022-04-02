/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 00:35:39 by ejahan            #+#    #+#             */
/*   Updated: 2022/04/02 11:27:29 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *str, t_struct *minish)
{
	int			pid;
	pid_t		status;
	static int	nbr_line = 1;
	char		*line;

	line = NULL;
	status = 0;
	pid = fork();
	if (pid == -1)
	{
		g_sig_error = 127;
		return ;
	}
	if (pid != 0)
	{
		signal(SIGINT, SIG_IGN);
		handle_father(minish, status, pid);
	}
	else
	{
		signal(SIGINT, handler_here_doc);
		while (line == NULL || ft_strcmp(line, str) != 0)
		{
			if (line != NULL)
				free(line);
			line = readline("> ");
			nbr_line++;
			if (line == NULL)
			{
				ctrl_d_hd(str, nbr_line);
				return ;
			}
		}
	}
	free(line);
}

t_list_hd	*recup_arg_here_doc(char *end, t_list_hd *hd, t_struct *minish)
{
	int			pid;
	pid_t		status;
	static int	nbr_line = 1;
	char		*line;
	char		*str;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		g_sig_error = 127;
		return (hd);
	}
	line = NULL;
	if (pid != 0)
	{
		signal(SIGINT, SIG_IGN);
		handle_father(minish, status, pid);
	}
	else
	{
		signal(SIGINT, handler_here_doc);
		str = ft_strdup(end);
		free(hd->first->here_doc);
		delete_hd(hd);
		while (line == NULL || ft_strcmp(line, str) != 0)
		{
			if (line != NULL)
				insertion_here_doc(hd, get_var_hd(line, minish));
			free(line);
			line = readline("> ");
			nbr_line++;
			if (line == NULL)
				return (ctrl_d(str, hd, nbr_line));
		}
		free(str);
		free(line);
		exit (g_sig_error);
	}
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
