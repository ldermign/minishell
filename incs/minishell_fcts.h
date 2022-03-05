/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_fcts.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:50:38 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/05 06:20:07 by ejahan           ###   ########.fr       */
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
**	PIPE
*/

void	there_is_pipe(t_struct *ms, char *prompt);

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
void	execute_cmd(t_struct *ms, char *path, char **args, char **exec_args_only, char **env);
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
// void	reboot_struct_std(t_red_std *std);
void	init_struct_it(t_it *it);
void	close_all_fd(t_red_std *std);
void	init_struct_pipe(t_pipe *pipe, t_struct *ms);

/*
**	TEMPORAIRE
*/

void	print_tab_char(char **tabl);
void	print_env_ms(t_env_ms **stack);

/*
**		>>>>>>>>>  PARSING  <<<<<<<<<
*/

//		>>>>>>>>>   initialisations
void		init_parsing(t_parsing *parsing);
t_list_arg	*init_args(void);
//		>>>>>>>>>   list
int			insertion(t_list_arg *list, char *new_arg);
int			free_list(t_list_arg *list);
int			delete(t_list_arg *list);
void		print_list(t_list_arg *list);
//		>>>>>>>>>	parsing
int			parsing(char *line, t_struct *minish);
//		>>>>>>>>>	recup_args
int			recup_pipe(char *line, t_struct *minishell);
int			recup_args(char *line, t_struct *minishell);
char		**interpret_args(char *line, char	**tab_arg, t_struct *minish);
char		**sep_and_check_args(t_args *arg, t_struct *minish);
int			pass_quotes(char *line);
// 		>>>>>>>>>	count_arg
int			pass_arg_count(char *line, t_struct *minish);
// 		>>>>>>>>>	utils
int			is_variable_char(char c);
int			pass_variable(char *line);
int			pass_redir(char *line, t_struct *minish);
int			pass_quotes(char *line);
int			error_malloc(t_struct *minish);
// 		>>>>>>>>>	empty_args
int			is_empty(char *line, t_struct *minish);
// 		>>>>>>>>>	len_arg
int			len_arg(char *line, t_struct *minish);
int 		len_double_quotes(char *line, t_struct *minish);
int 		len_simple_quote(char *line, t_struct *minish);
//      >>>>>>>>>   len_variable
int 		len_variable(char *line, t_struct *minish);
// 		>>>>>>>>>	fill_arg
int			fill_arg2(char *line, char *str, t_struct *minish);
int			fill_simple_quote(char *line, char *str, t_struct *minish);
int			fill_double_quotes(char *line, char *str, t_struct *minish);
// 		>>>>>>>>>	fill_variable
int			fill_variable(char *line, char *str, t_struct *minish);
//      >>>>>>>>>   echo
char		*recup_echo(char **args, t_struct *minish);
//      >>>>>>>>>   list_ok
// t_list_arg	*new_list(t_list_arg *list);
t_list_arg	*reverse_list(t_list_arg *list);
//      >>>>>>>>>   recup_redir
char		**recup_redir(char *line, t_struct *minish);
//      >>>>>>>>>   recup_pipe
int			check_pipe2(char *line, t_struct *minish);
int			recup_pipe2(char *line, t_struct *minish, int i);
int			pass_arg(char *line, t_struct *minish);
//      >>>>>>>>>   signals
void		handle_signal_child(int sig);
void		handle_signal(int sig);
char		*error_malloc_null(t_struct *minish);
int			double_dollar(t_struct *minish);
int			len_sig_error(t_struct *minish);
int			if_is_empty(char *line, int i);
int			fill_double_dollar(t_struct *minish, char *str);
int			fill_sig_error(t_struct *minish, char *str);
int			count_redir(char *line);

#endif
