/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:44:31 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/13 21:51:57 by ldermign         ###   ########.fr       */
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
	while (ret != -1)
	{
		last = ret;
		name_file = args[ret + 1];
		fd = open(name_file, O_CREAT, 0644);
		if (fd == -1)
			perror("bash"); // arranger le message d'erreur
		ret = get_name_file_redir(args, ret);
		close(fd);
		if (ret == last)
			break ;
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
		fd = open(name_file, O_WRONLY | O_APPEND, 0644);
	else
		fd = open(name_file, O_WRONLY | O_TRUNC, 0644);
	write(fd, ms->parsing.result, ft_strlen(ms->parsing.result));
	write(fd, "\n", 1);
	close(fd);
	return (EXIT_SUCCESS);
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

int	exec_redirection_1_3(t_struct *ms, char **args, char *name_file)
{
	int		fd;
	int		old_stdout;
	int		redir;
	char	**exec_args_only;
	char	*good_path;

	old_stdout = dup(1);
	if (ft_pos_strstr(args[0], ">") != -1 || ft_pos_strstr(args[0], ">>") != -1)
	{
		if (ft_pos_strstr(args[0], ">") != -1)
			fd = open(name_file, O_WRONLY | O_TRUNC, 0644);
		return (EXIT_SUCCESS);
	}
	redir = pos_last_redir(args);
	if (ft_pos_strstr(args[redir], ">>") != -1)
		fd = open(name_file, O_WRONLY | O_APPEND, 0644);
	else
		fd = open(name_file, O_WRONLY | O_TRUNC, 0644);
	printf("%d\n", fd);
	dup2(fd, 1);
	exec_args_only = get_args_exec(args);
	good_path = working_path(ms->env.path, exec_args_only[0]);
	execute_cmd(good_path, exec_args_only, ms->env.env_bash);
	close(fd);
	dup2(old_stdout, 1);
	return (EXIT_SUCCESS);
}

int	exec_redirection_2_4(t_struct *ms, char **args)
{(void)ms;(void)args;
	return(EXIT_SUCCESS);
}

int	get_redirections(t_struct *ms, char **args, int which)
{
	char	*name_file;

	if (which == 1 | which == 3)
	{
		name_file = create_all_files(args);
		if (ft_pos_strstr(args[0], "echo") != -1)
			return (echo_in_redir(ms, args, name_file));
		else
			return (exec_redirection_1_3(ms, args, name_file));
	}
	else if (which == 2 | which == 4)
	{
		return (exec_redirection_2_4(ms, args));
	}
	return (EXIT_SUCCESS);
}
