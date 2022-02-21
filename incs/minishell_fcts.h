/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_fcts.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:50:38 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/21 14:35:12 by ldermign         ###   ########.fr       */
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
int		built_in_echo(t_struct *ms, char **args, char *prompt);
int	built_in_to_create(t_struct *ms, char **cmd_args, char *prompt);

/*
**	REDIRECTIONS
*/

int		get_redirections(t_struct *ms, char **args, int which);
int	get_good_fd(char **args, char *name_file, t_red_std *std, int *pipefd);
int	get_good_fd_built_in(char **args, char *name_file, t_red_std *std);

/*
**	UTILS REDIRECTIONS
*/

int	redirection_first(char *args);
int	only_right(char **args);
int	is_redir(char **args, char *str);
int	last_redir(char **args);
int	pos_last_redir_left(char **args);
int	pos_last_redir_right(char **args);

/*
**	UTILS
*/

char	**get_cmd_and_args_split(char *str);

/*
**	UTILS BUILT IN
*/

int		size_variable(char *prompt, int add, int pos);
int		light_parse_export(char *prompt);
int		light_parse_echo(char *str);
char	*create_path(char *path, char *cmd);
char	*get_good_variable(char *prompt, int size, int add, int pos);
char	*working_path(char **paths, char *name_fct);
void	execute_cmd(t_struct *ms, char *path, char **args, char **env);
int	is_built_in(char *str);

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
char	*get_variable_with_pos(t_env_ms **minishell, int pos);

/*
**	INIT
*/

void	init_struct_std(char **args, t_red_std *std, int which);
void	reboot_struct_std(t_red_std *std);
void	init_struct_it(t_it *it);
void	close_all_fd(t_red_std *std);

/*
**	TEMPORAIRE
*/

void	print_tab_char(char **tabl);
void	print_env_ms(t_env_ms **stack);

// 		>>>>>>>>>  parsing  <<<<<<<<<
int		parse_line(char *line, t_parsing *parsing);

//		>>>>>>>>> check commandes
void	parse_echo(char *line, t_parsing *parsing);
void	parse_cd(char *line, t_parsing *parsing);
void	parse_pwd(char *line, t_parsing *parsing);
void	parse_export(char *line, t_parsing *parsing);
void	parse_unset(char *line, t_parsing *parsing);
void	parse_env(char *line, t_parsing *parsing);
void	parse_exit(char *line, t_parsing *parsing);

//		>>>>>>>>> echo
void	fill_result(char *line, t_parsing *parsing);
int		find_len(char *line, t_parsing *parsing);
// parse_quotes
int		simple_quote(char *line, t_parsing *parsing);
int		double_quotes(char *line, t_parsing *parsing);
int		check_quotes_and_redir(char *line, t_parsing *parsing);

//		>>>>>>>>> error
void	error_command(char *line, t_parsing *parsing);
int		error_check(char *line, t_parsing *parsing, int i);

//		>>>>>>>>> redirections
void	parse_second_redir(char *line, t_parsing *parsing);
int		skip_redirections(char *line, t_parsing *parsing);
int		redirections(char *line, t_parsing *parsing);
void	parse_first_redir(char *line, t_parsing *parsing);
void	parse_third_redir(char *line, t_parsing *parsing);
void	parse_fourth_redir(char *line, t_parsing *parsing);
void	check_char_in_file_name(char c, t_parsing *parsing);

#endif