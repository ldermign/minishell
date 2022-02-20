/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_fcts.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:50:38 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/20 08:04:15 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FCTS_H
# define MINISHELL_FCTS_H

/*
**	START
*/

int		get_prompt(char *prompt, t_env *env);

/*
**	BUILT-IN
*/

void	command(char *prompt, t_struct *ms);
int		recup_var_envs(char **env, t_env *cpy_env);
int		built_in_cd(t_env *env, char **cmd_args);
int		built_in_pwd(void);
void	built_in_exit(t_env *env, char **cmd_args, char *prompt);
int		built_in_unset(t_env *env, char **args);
int		built_in_env(t_env_ms *stack);
int		built_in_echo(t_struct *ms, char *prompt);

/*
**	REDIRECTIONS
*/

int		get_redirections(t_struct *ms, char **args, int which);

/*
**	UTILS REDIRECTIONS
*/

int		redirection_in_file(char **cmd_args);

/*
**	UTILS
*/

char	**get_cmd_and_args_split(char *str);

/*
**	UTILS BUILT IN
*/

int		size_variable(char *prompt);
int		light_parse_export(char *prompt);
int		light_parse_echo(char *str);
char	*create_path(char *path, char *cmd);
char	*get_good_variable(char *prompt, int size);

/*
**	UTILS LIST
*/

void	free_lst(t_env_ms *stack);
void	add_var_env_minishell(t_env_ms **stack, char *str_var);
int		search_for_var_in_env(t_env_ms **stack, char *var);
void	supp_var_env_ms(t_env_ms **stack, int pos);
void	change_var_env_minishell(t_env_ms **minishell, char *str, int pos);
int		check_if_variable_already_exist(t_env_ms **minishell, char *str);
char	*get_variable(t_env_ms **minishell, char *str);
int		size_env(t_env_ms **minishell);

/*
**	Test
*/

void	test_redir_dup(t_struct *ms, char **args);

/*
**	TEMPORAIRE
*/

void	print_tab_char(char **tabl);
void	print_env_ms(t_env_ms **stack);

/*
**		>>>>>>>>>  PARSING  <<<<<<<<<
*/

//		>>>>>>>>>   initialisations
void	init_parsing(t_parsing *parsing);
t_list_arg	*init_args(void);
//		>>>>>>>>>   list
int		insertion(t_list_arg *list, char *new_arg);
int		free_list(t_list_arg *list);
int		delete(t_list_arg *list);
void	print_list(t_list_arg *list);
//		>>>>>>>>>	parsing
int		parsing(char *line, t_struct *minish);
//		>>>>>>>>>	recup_args
int		recup_pipe(char *line, t_struct *minishell);
int		recup_args(char *line, t_struct *minishell);
// 		>>>>>>>>>	arguments
// int 	interpret_args(char *line, char	**tab_arg, t_struct *minish);
char	**interpret_args(char *line, char	**tab_arg, t_struct *minish);
// 		>>>>>>>>>	sep_args
// int		sep_and_check_args(t_args *arg, t_struct *minish);
char	**sep_and_check_args(t_args *arg, t_struct *minish);
int		pass_quotes(char *line);
// 		>>>>>>>>>	count_arg
int		pass_arg_count(char *line, t_struct *minish);
// 		>>>>>>>>>	utils
int		is_variable_char(char c);
int		pass_variable(char *line);
int		pass_redir(char *line, t_struct *minish);
int		pass_quotes(char *line);
int		error_malloc(t_struct *minish);
// 		>>>>>>>>>	empty_args
int		is_empty(char *line, t_struct *minish);
// 		>>>>>>>>>	len_arg
int		len_arg(char *line, t_struct *minish);
int 	len_double_quotes(char *line, t_struct *minish);
int 	len_simple_quote(char *line, t_struct *minish);
//      >>>>>>>>>   len_variable
int 	len_variable(char *line, t_struct *minish);
// 		>>>>>>>>>	fill_arg
int		fill_arg2(char *line, char *str, t_struct *minish);
// 		>>>>>>>>>	fill_variable
int		fill_variable(char *line, char *str, t_struct *minish);
//      >>>>>>>>>   redir
int 	recup_redir(t_args *arg, t_struct *minish);
int 	count_redir(char *line, t_struct *minish);
int 	fill_redir(char *line, t_struct *minish);





/*
**		AVANT
*/

// int		parse_line(char *line, t_parsing *parsing);

// //		>>>>>>>>> check commandes
// void	parse_echo(char *line, t_parsing *parsing);
// void	parse_cd(char *line, t_parsing *parsing);
// void	parse_pwd(char *line, t_parsing *parsing);
// void	parse_export(char *line, t_parsing *parsing);
// void	parse_unset(char *line, t_parsing *parsing);
// void	parse_env(char *line, t_parsing *parsing);
// void	parse_exit(char *line, t_parsing *parsing);

// //		>>>>>>>>> echo
// void	fill_result(char *line, t_parsing *parsing);
// int		find_len(char *line, t_parsing *parsing);
// // parse_quotes
// int		simple_quote(char *line, t_parsing *parsing);
// int		double_quotes(char *line, t_parsing *parsing);
// int		check_quotes_and_redir(char *line, t_parsing *parsing);

// //		>>>>>>>>> error
// void	error_command(char *line, t_parsing *parsing);
// int		error_check(char *line, t_parsing *parsing, int i);

// //		>>>>>>>>> redirections
// void	parse_second_redir(char *line, t_parsing *parsing);
// int		skip_redirections(char *line, t_parsing *parsing);
// int		redirections(char *line, t_parsing *parsing);
// void	parse_first_redir(char *line, t_parsing *parsing);
// void	parse_third_redir(char *line, t_parsing *parsing);
// void	parse_fourth_redir(char *line, t_parsing *parsing);
// void	check_char_in_file_name(char c, t_parsing *parsing);

#endif
