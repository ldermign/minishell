/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_fcts.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:50:38 by ldermign          #+#    #+#             */
/*   Updated: 2022/01/18 15:59:39 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FCTS_H
# define MINISHELL_FCTS_H

/*
**	START
*/

int	get_prompt(char *prompt, t_env *env);

/*
**	BUILT-IN
*/

void start_built_in(char *prompt, t_env *env);
int	recup_var_envs(char **env, t_env *cpy_env);

/*
**	UTILS
*/

char	**get_cmd_and_args_split(char *str);

/*
**	TEMPORAIRE
*/

void	print_tab_char(char **tabl);


// 		>>>>>>>>>  parsing  <<<<<<<<<
int	parse_line(char *line, t_parsing *parsing);
// check commandes
void	parse_echo(char *line, t_parsing *parsing);
void	parse_cd(char *line, t_parsing *parsing);
void	parse_pwd(char *line, t_parsing *parsing);
void	parse_export(char *line, t_parsing *parsing);
void	parse_unset(char *line, t_parsing *parsing);
void	parse_env(char *line, t_parsing *parsing);
void	parse_exit(char *line, t_parsing *parsing);
// echo
void	fill_result(char *line, t_parsing *parsing);
int	find_len(char *line, t_parsing *parsing);
// error
int	error_command(char *line, t_parsing *parsing, char *str);
int	error_check(char *line, t_parsing *parsing, int i);

#endif