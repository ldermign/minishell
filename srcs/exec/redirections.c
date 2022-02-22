/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:44:31 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/22 13:56:58 by ldermign         ###   ########.fr       */
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
			if (args[i][1] == '\0')
				return (i);
			else if (args[i][1] && args[i][1] == '>' && args[i][2] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
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
		name_file = args[ret + 1];
		fd = open(name_file, O_CREAT, 0644);
		if (fd == -1)
		{
			sig_error = errno;
			perror("minishell"); // arranger le message d'erreur
		}
		ret = get_name_file_redir(args, ret);
		close(fd);
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

int	execution_redirection(t_struct *ms, char **args, t_red_std *std)
{
	char	**exec_args_only;
	char	*good_path;

	if (is_built_in(args[0]) == EXIT_SUCCESS)
	{
		get_good_fd_built_in(args, ms->std.name_file, std);
		built_in_to_create(ms, args, ms->prompt);
		// reboot_struct_std(&(ms->std));
		return (EXIT_SUCCESS);
	}
	exec_args_only = get_args_exec(args);
	good_path = working_path(ms->env.path, exec_args_only[0]);
	// get_good_fd(args, ms->std.name_file, std);
	// execute_cmd(ms, good_path, exec_args_only, ms->env.env_bash);
	execute_cmd(ms, good_path, args, ms->env.env_bash);
	// close_all_fd(std);
	return(EXIT_SUCCESS);
}

int	get_redirections(t_struct *ms, char **args, int which)
{
	if (which == 1 || which == 3)
		ms->std.name_file = create_all_files(args); // verifier qu'il existe bien, car parfois pas de fichier
	if (redirection_first(args[0]) == EXIT_SUCCESS)
		return (first_arg_is_redir(args, &(*ms).std, which));
	// if (get_good_fd(args, name_file, &(*ms).std) == EXIT_FAILURE)
	// {
	// 	sig_error = errno;
	// 	perror("minishell");
	// 	return (EXIT_FAILURE);
	// }
	// if (ft_pos_strstr(args[0], "wc") != -1 && ms->std.both == 0 && ms->std.dbl_l == 1)
	// 	get_args_wc_dbl_l(ms, args); a voir
	execution_redirection(ms, args, &(*ms).std);
	return (EXIT_SUCCESS);
}

/*

int	how_many_redirec(char **args)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (args[i])
	{
		if (args[i][1] != '\0'
			&& (args[i][0] == '>' || args[i][0] == '<'))
		{
			if (args[i][0] == '>' && args[i][1] == '>' && args[i][2] == '\0')
				ret++;
			if (args[i][0] == '<' && args[i][1] == '<' && args[i][2] == '\0')
				ret++;;
		}
		else if (args[i][0] == '>' && args[i][1] == '\0')
			ret++;
		else if (args[i][0] == '<' && args[i][1] == '\0')
			ret++;
		i++;
	}
	return (ret);
}

*/