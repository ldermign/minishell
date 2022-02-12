/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:44:31 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/12 19:44:40 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_in_file(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i])
	{
		if (cmd_args[i][1] != '\0'
			&& (cmd_args[i][0] == '>' || cmd_args[i][0] == '<'))
		{
			if (cmd_args[i][0] == '>' && cmd_args[i][1] == '>' && cmd_args[i][2] == '\0')
				return (3);
			if (cmd_args[i][0] == '<' && cmd_args[i][1] == '<' && cmd_args[i][2] == '\0')
				return (4);
		}
		else if (cmd_args[i][0] == '>' && cmd_args[i][1] == '\0')
			return (1);
		else if (cmd_args[i][0] == '<' && cmd_args[i][1] == '\0')
			return (2);
		i++;
	}
	return (-1);
}

int	ft_pos_str_in_tab(char **tabl, char *str)
{
	int		i;
	int		j;
	size_t	size;

	i = 0;
	j = 0;
	size = ft_strlen(str);
	while (tabl[i])
	{
		if (ft_strlen(tabl[i]) != size)
			i++;
		while (tabl[i][j] && str[j] && tabl[i][j] == str[j])
			j++;
		if (tabl[i][j] == '\0' && str[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

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

char	*last_redir(char **args)
{
	int		i;
	char	*last;

	i = 0;
	last = NULL;
	while (args[i])
	{
		if (args[i][0] == '>')
		{
			if (args[i][1] == '\0')
				last = args[i];
			else if (args[i][1] && args[i][1] == '>' && args[i][2] == '\0')
				last = args[i];
		}
		i++;
	}
	return (last);
}

int	pos_last_redir(char **args)
{
	int	i;
	int	last;

	i = 0;
	last = 0;
	while (args[i])
	{
		if (args[i][0] == '>')
		{
			if (args[i][1] == '\0')
				last = i;
			else if (args[i][1] && args[i][1] == '>' && args[i][2] == '\0')
				last = i;
		}
		i++;
	}
	return (last);
}

char	*create_all_files(char **args)
{
	int		fd;
	int		ret;
	int		last;
	char	*name_file;

	ret = get_name_file_redir(args, 0);
	last = pos_last_redir(args);
	if (how_many_redirec(args) != 1)
	{
		while (ret != -1)
		{
			last = ret;
			name_file = args[ret + 1];
			fd = open(name_file, O_CREAT, 0644);
			ret = get_name_file_redir(args, ret);
			close(fd);
		}
	}
	name_file = args[last + 1];
	return (name_file);
}

int	echo_in_redir(t_struct *ms, char **args, char *name_file)
{
	int	fd;
	int	last;

	fd = 0;
	last = pos_last_redir(args);
	if (ft_pos_strstr(args[last], ">>") != -1)
		fd = open(name_file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(name_file, O_WRONLY | O_CREAT, 0644);
	write(fd, ms->parsing.result, ft_strlen(ms->parsing.result));
	write(fd, "\n", 1);
	close(fd);
	return (EXIT_SUCCESS);
}

int	exec_redirection(t_struct *ms, char **args, char *name_file)
{(void)ms;(void)args;(void)name_file;	// utiliser dup et dup2
	int		fd;
	char	*good_path;

	fd = open(name_file, O_WRONLY, 0644);
	dup2(fd, 1);
	good_path = working_path(ms->env.path, args[0]);
	execute_cmd(good_path, args, ms->env.env_bash);
	return (EXIT_SUCCESS);
}

int	get_redirections(t_struct *ms, char **args, int which)
{ // to_print = ms->parsing.result
(void)ms;(void)args;(void)which;
	char	*name_file;

	if (which == 1 | which == 3)
	{
		name_file = create_all_files(args);
		if (ft_pos_strstr(args[0], "echo") != -1)
			return (echo_in_redir(ms, args, name_file));
		else
			return (exec_redirection(ms, args, name_file));
		// return (redirection1(ms, args));
	}
	// else if (which == 2)
	// 	return (redirection2(ms));
	// if (which == 3)
	// 	return (redirection3(ms, args));
	// else
	// 	return (redirection4(ms));
	return (EXIT_SUCCESS);
}
