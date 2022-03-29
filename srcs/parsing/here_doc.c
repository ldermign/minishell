/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 00:35:39 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/29 13:37:08 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *str)
{
	static int	nbr_line = 0;
	char		*line;

	line = readline("> ");
	if (line == NULL)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		fprintf(stderr, "minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", nbr_line, str);
		g_sig_error = 0;
		return ;
	}
	while (ft_strcmp(line, str) != 0)
	{
		free(line);
		line = readline("> ");
		nbr_line++;
		if (line == NULL)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			fprintf(stderr, "minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", nbr_line, str);
			g_sig_error = 0;
			return ;
		}
	}
	free(line);
}

void	handle_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_sig_error = 130;
		exit (g_sig_error);
	}
}

static t_list_hd	*ctrl_d(char *str, t_list_hd *hd, int nbr_line)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	fprintf(stderr, "minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", nbr_line, str);
	g_sig_error = 0;
	free(str);
	return (hd);
}

t_list_hd	*recup_arg_here_doc(char *end, t_list_hd *hd)
{
	static int	nbr_line = 1;
	char		*line;
	char		*str;

	str = ft_strdup(end);
	free(hd->first->here_doc);
	delete_hd(hd);
	signal(SIGINT, handle_here_doc);
	line = readline("> ");
	if (line == NULL)
		return (ctrl_d(str, hd, nbr_line));
	while (ft_strcmp(line, str) != 0)
	{
		insertion_here_doc(hd, ft_strdup(line));
		line = readline("> ");
		nbr_line++;
		if (line == NULL)
		{
			rl_on_new_line();
			fprintf(stderr, "minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", nbr_line, str);
			g_sig_error = 0;
			free(str);
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
