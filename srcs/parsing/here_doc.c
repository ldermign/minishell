/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 00:35:39 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/12 05:57:02 by ejahan           ###   ########.fr       */
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

int	recup_here_doc(char *line, t_struct *minish)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (error_malloc(minish));
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i] = line[i];
		i--;
	}
	insertion_here_doc(minish->args->first->here_doc, str);
	print_list_hd(minish->args->first->here_doc);
	return (0);
}

void	exec_here_doc(t_list_arg *args)
{
	t_args		*tmp;
	t_here_doc	*re_tmp;

	tmp = args->first;
	while (args->first != NULL)
	{
		printf("exec_here_doc\n");
		args->first->here_doc = reverse_list_hd(args->first->here_doc);
		printf("exec_here_doc2\n");
		print_list_hd(args->first->here_doc);
		re_tmp = args->first->here_doc->first;
		printf("exec_here_doc\n");
		while (args->first->here_doc->first != NULL)
		{
			printf("exec_here_doc\n");
			if (args->first->here_doc->first->next == NULL)
			{
				here_doc(args->first->here_doc->first->here_doc);
				// here_doc + recup
			}
			else
				here_doc(args->first->here_doc->first->here_doc);
			args->first->here_doc->first = args->first->here_doc->first->next;
		}
		args->first = args->first->next;
		args->first->here_doc->first = re_tmp;
		printf("exec_here_doc\n");
	}
	args->first = tmp;
}
