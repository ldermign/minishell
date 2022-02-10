/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:44:31 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/10 15:17:12 by ldermign         ###   ########.fr       */
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
			if (cmd_args[i][0] == '>' && cmd_args[i][1] == '>')
				return (3);
			if (cmd_args[i][0] == '<' && cmd_args[i][1] == '<')
				return (4);
		}
		else if (cmd_args[i][0] == '>')
			return (1);
		else if (cmd_args[i][0] == '<')
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

int	how_many_redirec(char **args, char *str)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	ret = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j] && str[j] && args[i][j] == str[j])
			j++;
		if (args[i][j] == '\0' && str[j] == '\0')
			ret++;
		i++;
	}
	return (ret);
}

int	pos_last_redir(char **args, char *str, int last)
{
	int	i;
	int	j;

	if (last != 0)
		i = last + 1;
	else
		i = last;
	while (args[i])
	{
		j = 0;
		while (args[i][j] && str[j] && args[i][j] == str[j])
			j++;
		if (args[i][j] == '\0' && str[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

int	redirection1(t_struct *ms, char **args)
{
	int		fd;
	int		ret;
	char	*name_file;

	if (how_many_redirec(args, ">") > 1)
	{
		ret = pos_last_redir(args, ">", 0);
		while (ret != -1)
		{
			name_file = args[ret + 1];
			fd = open(name_file, O_WRONLY | O_CREAT, 0644);
			ret = pos_last_redir(args, ">", ret);
		}
	}
	else
	{
		name_file = args[ft_pos_str_in_tab(args, ">") + 1];
		fd = open(name_file, O_WRONLY | O_CREAT, 0644);
	}
	write(fd, ms->parsing.result, ft_strlen(ms->parsing.result));
	write(fd, "\n", 1);
	return (EXIT_SUCCESS);
}

int	redirection3(t_struct *ms, char **args)
{
	int		fd;
	char	*name_file;

	name_file = args[ft_pos_str_in_tab(args, ">") + 1];
	if (name_file == NULL)		// normalement, gere dans le parsing
		return (EXIT_FAILURE);	// normalement, gere dans le parsing
	fd = open(name_file, O_WRONLY | O_APPEND | O_CREAT, 0644); // verifier le 0644
	write(fd, ms->parsing.result, ft_strlen(ms->parsing.result));
	write(fd, "\n", 1);
	return (EXIT_SUCCESS);
}

int	get_redirections(t_struct *ms, char **args, int which)
{ // to_print = ms->parsing.result
	if (which == 1)
		return (redirection1(ms, args));
	// else if (which == 2)
	// 	return (redirection2(ms));
	else if (which == 3)
		return (redirection3(ms, args));
	// else
	// 	return (redirection4(ms));
	return (EXIT_SUCCESS);
}