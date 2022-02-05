/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_fcts.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:50:38 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/04 15:13:19 by ldermign         ###   ########.fr       */
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
int	built_in_cd(t_env *env, char **cmd_args);
int	built_in_pwd();
void	built_in_exit(t_env *env, char **cmd_args, char *prompt);
int	built_in_unset(t_env *env, char **args);
int	built_in_env(t_env_ms *stack);
int	built_in_echo(char *prompt);

/*
**	UTILS
*/

char	**get_cmd_and_args_split(char *str);

/*
**	UTILS BUILT IN
*/

int	size_variable(char *prompt);
int	light_parse_export(char *prompt);
int	light_parse_echo(char *str);
char	*create_path(char *path, char *cmd);
char	*get_good_variable(char *prompt);

/*
**	UTILS LIST
*/

void	free_lst(t_env_ms *stack);
void	add_var_env_minishell(t_env_ms **stack, char *str_var);
int	search_for_var_in_env(t_env_ms **stack, char *var);
void	supp_var_env_ms(t_env_ms **stack, int pos);
void	change_var_env_minishell(t_env_ms **minishell, char *str, int pos);
int	check_if_variable_already_exist(t_env_ms **minishell, char *str);

/*
**	TEMPORAIRE
*/

void	print_tab_char(char **tabl);
void	print_env_ms(t_env_ms **stack);


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
void	skip_redirections(char *line, t_parsing *parsing);
void	redirections(char *line, t_parsing *parsing);
// error
void	error_command(char *line, t_parsing *parsing);
int	error_check(char *line, t_parsing *parsing, int i);

#endif