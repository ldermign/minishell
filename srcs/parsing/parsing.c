/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:42:38 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/12 08:03:01 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_file(char *args, t_struct *minish)
{
	int		fd;
	char	*name_file;

	name_file = recup_name(args);
	fd = open(name_file, O_CREAT, 0644);
	if (fd == -1)
	{
		minish->parsing.error = 1;
		printf("error create file\n");
		return ; // arranger le message d'erreur
	}
	close(fd);
	free(name_file);
}

void	check_file(char *arg, t_struct *minish)
{
	int	i;
	int	fd;

	i = 0;
	while (arg[i] && arg[i] != ' ')
		i++;
	fd = open(&arg[i], O_RDONLY);
	if (fd == -1)
	{
		printf("no such file or directory\n") // a changer
		minish->aprsing.error = 1;
	}
	else
		close(fd);
}

void	redirections(t_list_arg *args, t_struct *minish)
{
	t_args		*tmp;
	int			i;

	tmp = args->first;
	while (args->first != NULL)
	{
		i = 0;
		while (args->first->redir[i] != NULL)
		{
			if (args->first->redir[i][0] == '>')
				create_file(args->first->redir[i], minish);
			else
				check_file(args->first->redir[i], minish);
			i++;
			if (minish->parsing.error != 0)
				return ;
		}
		args->first = args->first->next;
	}
	args->first = tmp;
}

// void	redirections(t_struct *minish)
// {
// 	while (minish-)
// 	// tant que redir[i] 
// 	// creer les fichiers si '>' ou '>>'
// 	// verifier si les fichiers existent si '<'
// 	// si error -> return -1 + parsing error = 1
// }

int	parsing(char *line, t_struct *minish)
{
	minish->args = init_args();
	init_parsing(&minish->parsing);
	if (recup_args(line, minish) == -1)
	{
		minish->args = reverse_list(minish->args);
		exec_here_doc(minish->args);
		if (minish->parsing.error == 2)
			free_list2(minish->args);
		if (minish->parsing.error == 3)
			free_list3(minish->args);
		return (-1);
	}
	redirections(minish);
	if (minish->parsing.error != 0)
	{
		free_list(minish->args);
		return (-1);
	}
	minish->parsing.nb_pipe -= 1;
	return (0);
}

int	recup_pipe(char *line, t_struct *minish)
{
	int	i;
	int	j;

	while (line[minish->parsing.i_line])
	{
		i = 0;
		j = 0;
		if (check_pipe2(&line[minish->parsing.i_line], minish) == -1)
			return (-1);
		while (line[minish->parsing.i_line + i]
			&& line[minish->parsing.i_line + i] != '|')
		{
			i += pass_arg(&line[minish->parsing.i_line + i], minish);
			if (minish->parsing.error != 0)
				return (-1);
		}
		recup_pipe2(line, minish, i);
		minish->parsing.nb_pipe++;
		if (minish->parsing.error != 0)
			return (-1);
		if (line[minish->parsing.i_line] != '\0')
			minish->parsing.i_line++;
	}
	return (0);
}

int	recup_args(char *line, t_struct *ms)
{
	t_args	*tmp;

	if (recup_pipe(line, ms) == -1)
		return (-1);
	ms->args = reverse_list(ms->args);
	tmp = ms->args->first;
	while (ms->args->first != NULL)
	{
		ms->parsing.nb_arg = 0;
		ms->args->first->arg_to_pass = sep_and_check_args(ms->args->first, ms);
		if (ms->parsing.error != 0)
		{
			ms->args->first = tmp;
			return (-1);
		}
		ms->args->first->redir = recup_redir(ms->args->first->command, ms);
		if (ms->parsing.error != 0)
		{
			ms->args->first = tmp;
			return (-1);
		}
		ms->args->first = ms->args->first->next;
	}
	ms->args->first = tmp;
	return (0);
}
