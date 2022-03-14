/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:44:31 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/14 14:29:21 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_name_file_redir(char **args, int last)
{
	int	i;

	i = 0;
	if (last != 0)
		i = last + 1;
	else
		i = last;
	while (args[i])
	{
		if (args[i][0] == '>')
		{
			if (args[i][1] == ' ')
				return (i);
			else if (args[i][1] && args[i][1] == '>' && args[i][2] == ' ')
				return (i);
		}
		i++;
	}
	return (-1);
}

char	*recup_name(char *args)
{
	char	*name;
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	j = 0;
	while (args[i] && args[i] != ' ')
		i++;
	i++;
	while (args[i + j])
		j++;
	name = malloc(sizeof(char) * j + 1);
	if (name == NULL)
		return (NULL);
	name[j] = '\0';
	while (k < j)
		name[k++] = args[i++];
	return (name);
}

char	*create_all_files(char **args)
{
	int		fd;
	int		ret;
	int		last;
	char	*name_file;

	ret = get_name_file_redir(args, 0);
	last = last_redir(args);
	while (ret != -1)
	{
		last = ret;
		name_file = recup_name(args[ret]);
		fd = open(name_file, O_CREAT, 0644);
		if (fd == -1)
		{
			g_sig_error = errno;
			perror("minishell"); // arranger le message d'erreur
		}
		ret = get_name_file_redir(args, ret);
		close(fd);
		free(name_file);
		if (ret == last)
			break ;
	}
	name_file = args[last + 1];
	return (name_file);
}

static int	size(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (args[i][0] != '-')
			break ;
		i++;
	}
	return (i);
}

char	**get_args_exec(char **args)
{
	int		i;
	int		len;
	char	**tabl;

	i = 0;
	len = size(args);
	tabl = malloc(sizeof(char *) * len + 1);
	if (tabl == NULL)
		return (NULL);
	while (i < len)
	{
		tabl[i] = args[i];
		i++;
	}
	tabl[i] = NULL;
	return (tabl);
}

int	first_arg_is_redir(char **args, t_red_std *std, int which)
{
	char	*line;

	if (which == 1)
	{
		std->fd_to_write = open(std->name_file, O_WRONLY | O_TRUNC, 0644);
		close(std->fd_to_write);
	}
	// if (which == 2)
	// {
		// std->fd = dup(0);
	// }
	else if (which == 4)
	{
		line = readline("> ");
		while (ft_strcmp(line, args[std->last_left + 1]) != 0)
			line = readline("> ");
	}
	return (EXIT_SUCCESS);
}

int	execution_redirection(t_struct *ms, t_args *args, t_red_std *std)
{
	char	*good_path;

	if (is_built_in(args->arg_to_pass[0]) == EXIT_SUCCESS)
	{
		get_good_fd_built_in(args->redir, ms->std.name_file, std);
		built_in_to_create(ms, ms->args->first);
		return (EXIT_SUCCESS);
	}
	good_path = working_path(ms->env.path, args->arg_to_pass[0]);
	execute_cmd(ms, good_path, args->redir, args->arg_to_pass, ms->env.env_bash);
	return (EXIT_SUCCESS);
}

int	get_redirections(t_struct *ms, t_args *args, int which)
{
	if (which == 1 || which == 3)
	{
		ms->std.name_file = create_all_files(args->redir); // verifier qu'il existe bien, car parfois pas de fichier
	}
	// if (redirection_first(args->command) == EXIT_SUCCESS) // a changer
	// 	return (first_arg_is_redir(args->redir, &(*ms).std, which));
	// printf("ici\n");
	execution_redirection(ms, args, &(*ms).std);
	return (EXIT_SUCCESS);
}
