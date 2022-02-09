/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:44:31 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/09 14:15:54 by ldermign         ###   ########.fr       */
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

int	redirection1(t_struct *ms, char **args)
{
	int		fd;
	char	*name_file;

	name_file = args[ft_pos_str_in_tab(args, ">") + 1];
	if (name_file == NULL)		// normalement, gere dans le parsing
		return (EXIT_FAILURE);	// normalement, gere dans le parsing
	fd = open(name_file, O_WRONLY | O_CREAT, 0644); // verifier le 0644
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