/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:08:08 by elisa             #+#    #+#             */
/*   Updated: 2022/02/07 16:36:36 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_else(char *line, t_parsing *parsing)
{
	while (line[parsing->i_line] && line[parsing->i_line] != '<'
		&& line[parsing->i_line] != '>' && line[parsing->i_line] != '|')
		parsing->i_line++;
}

// int	check_command(char *line, t_parsing *parsing)
// {
// 	if (ft_strlen(line) > 3
// 		&& ft_memcmp("echo", &line[parsing->i_line], 4) == 0)
// 		parse_echo(line, parsing);
// 	else if (ft_strlen(line) > 1
// 		&& ft_memcmp("cd", &line[parsing->i_line], 2) == 0)
// 		parse_cd(line, parsing);
// 	else if (ft_strlen(line) > 2
// 		&& ft_memcmp("pwd", &line[parsing->i_line], 3) == 0)
// 		parse_pwd(line, parsing);
// 	else if (ft_strlen(line) > 5
// 		&& ft_memcmp("export", &line[parsing->i_line], 6) == 0)
// 		parse_export(line, parsing);
// 	else if (ft_strlen(line) > 4
// 		&& ft_memcmp("unset", &line[parsing->i_line], 5) == 0)
// 		parse_unset(line, parsing);
// 	else if (ft_strlen(line) > 2
// 		&& ft_memcmp("env", &line[parsing->i_line], 3) == 0)
// 		parse_env(line, parsing);
// 	else if (ft_strlen(line) > 3
// 		&& ft_memcmp("exit", &line[parsing->i_line], 4) == 0)
// 		parse_exit(line, parsing);
// 	else
// 		parse_else(line, parsing);
// 	if (parsing->error != 0)
// 		return (-1);
// 	return (0);
// }

int	check_command(char *line, t_parsing *parsing)
{
	if (ft_memcmp("echo", &line[parsing->i_line], 4) == 0)
		parse_echo(line, parsing);
	else if (ft_memcmp("cd", &line[parsing->i_line], 2) == 0)
		parse_cd(line, parsing);
	else if (ft_memcmp("pwd", &line[parsing->i_line], 3) == 0)
		parse_pwd(line, parsing);
	else if (ft_memcmp("export", &line[parsing->i_line], 6) == 0)
		parse_export(line, parsing);
	else if (ft_memcmp("unset", &line[parsing->i_line], 5) == 0)
		parse_unset(line, parsing);
	else if (ft_memcmp("env", &line[parsing->i_line], 3) == 0)
		parse_env(line, parsing);
	else if (ft_memcmp("exit", &line[parsing->i_line], 4) == 0)
		parse_exit(line, parsing);
	else
		parse_else(line, parsing);
	if (parsing->error != 0)
		return (-1);
	return (0);
}

// int	check_redirection(char *line, t_parsing *parsing)
// {
// 	return (0);
// }

// int	check_pipe(char *line, t_parsing *parsing)
// {
// 	if (line[parsing->i_line - 1] != ' ' || line[parsing->i_line + 1] != ' ')
// 	{
		// parsing->ret_error = malloc(sizeof(char) * 40);
		// if (parsing->ret_error == NULL)
		// 	return (-1);
		// ft_strcpy(parsing->ret_error, "syntax error : bad character around '|'");
		// return (-1);
	// }
// 	return (0);
// }

int	parse_line(char *line, t_parsing *parsing)
{
	if (line[0] == '\0')
		return (0);
	while (line[parsing->i_line] == ' ')
		parsing->i_line++;
	if (check_command(line, parsing) == -1)
		return (-1);
	// if (check_redirection(line, parsing) == -1)
	// 	return (-1);
	// if (check_pipe(line, parsing) == -1)
	// 	return (-1);
	return (0);
}

// https://putaindecode.io/articles/maitriser-les-redirections-shell/
// https://www.pierre-giraud.com/shell-bash/redirection-gestion-flux/
