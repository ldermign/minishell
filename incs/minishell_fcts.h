/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_fcts.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:50:38 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/19 19:13:19 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FCTS_H
# define MINISHELL_FCTS_H

/*
**	BUILT-IN SOLO
*/

int			built_in(t_struct *ms, t_args *cmd);
int			built_in_export(t_args *cmd, t_env_ms **env);
int			recup_var_envs(char **env, t_env *cpy_env);
int			built_in_cd(t_env *env, char *new_to_go);
int			built_in_pwd(void);
void		built_in_exit(t_env *env, char **cmd, char *prompt);
int			built_in_unset(t_env *env, t_args *cmd);
int			built_in_env(t_env_ms *stack);
int			built_in_echo(t_struct *ms);

/*
**	BUILT-IN PIPE
*/

void		built_in_with_pipe(t_struct *ms, t_args *cmd, t_pipe *pipex);

/*
**	REDIRECTIONS
*/

int	redirection(t_struct *ms, t_args *stack, t_pipe	*pipex);
int			get_good_fd_built_in(char **args, char *name_file, t_red_std *std);

/*
**	PIPE
*/

void		there_is_pipe(t_struct *ms);

/*
**	EXECVE
*/

int	execute_cmd_execve(t_struct *ms, char **cmd);
int	execute_cmd_with_fork(t_struct *ms, t_args *stack);

/*
**	SIG ERROR
*/

int	sig_error(char *str, int nbr);

/*
**	UTILS REDIRECTIONS
*/

int			redirection_first(char *args);
int			only_right(char **args);
int			is_redir(char **args, char *str);
int			last_redir(char **args);
int			pos_last_redir_left(char **args);
int			pos_last_redir_right(char **args);

/*
**	UTILS
*/

char		**get_cmd_and_args_split(char *str);

/*
**	UTILS BUILT IN
*/

int			size_variable(char *prompt, int add, int pos);
int			light_parse_export(char *prompt);
int			light_parse_echo(char *str);
char		*get_good_variable(char *prompt, int size, int add, int pos);
int			is_built_in(char *str);

/*
**	UTILS LIST
*/

void		free_lst(t_env_ms *stack);
void		add_var_env_minishell(t_env_ms **stack, char *str_var);
int			search_for_var_in_env(t_env_ms **stack, char *var);
void		supp_var_env_ms(t_env_ms **stack, int pos);
void		change_var_env_minishell(t_env_ms *minishell, char *str, int pos);
int			check_if_variable_already_exist(t_env_ms *minishell, char *str);
char		*get_variable(t_env_ms *minishell, char *str);
int			size_env(t_env_ms **minishell);
char		*get_variable_with_pos(t_env_ms *minishell, int pos);

/*
**	OTHERS EXECUTABLES
*/

int	other_executable(t_struct *ms, t_args *cmd, char **env_bash);
int	is_new_executable(char *str);

/*
**  UTILS PIPE
*/

/*
**	INIT
*/

void		init_struct_std(char **args, t_red_std *std, int which);
// void	reboot_struct_std(t_red_std *std);
void		init_struct_it(t_it *it);
void		init_struct_pipe(t_pipe *pipe, t_struct *ms);

/*
**	FREE
*/

void		free_all_cmds_pompt(t_args *stack);

/*
**	TEMPORAIRE A SUPPRIMEEEEEERRRRRR
*/

void		print_tab_char(char **tabl);
void		print_env_ms(t_env_ms **stack);
void		print_stack_cmd(t_args *stack);

/*
**		>>>>>>>>>  PARSING  <<<<<<<<<
*/

char    	**arg_list(t_list_hd *hd, t_struct *minish);
void		check_file(char *arg, t_struct *minish);
int			check_pipe2(char *line, t_struct *minish);
int			count_redir(char *line);
void		create_file(char *args, t_struct *minish);
int			delete(t_list_arg *list);
int			delete_hd(t_list_hd *list);
int			double_dollar(t_struct *minish);
int			error_malloc(t_struct *minish);
char		*error_malloc_null(t_struct *minish);
void		exec_here_doc(t_list_arg *args, t_struct *minish);
int			fill_arg2(char *line, char *str, t_struct *minish);
int			fill_double_dollar(t_struct *minish, char *str);
int			fill_double_quotes(char *line, char *str, t_struct *minish);
int			fill_sig_error(t_struct *minish, char *str);
int			fill_simple_quote(char *line, char *str, t_struct *minish);
int			fill_variable(char *line, char *str, t_struct *minish);
int			free_list(t_list_arg *list);
int			free_list2(t_list_arg *list);
int			free_list3(t_list_arg *list);
int			free_list_hd(t_list_hd *list);
void		handle_signal(int sig);
void		handle_signal_child(int sig);
int			if_is_empty(char *line, int i);
t_list_arg	*init_args(void);
t_list_hd	*init_here_doc(void);
void		init_parsing(t_parsing *parsing);
int			insertion(t_list_arg *list, char *new_arg);
int			insertion_here_doc(t_list_hd *list, char *new_arg);
int			is_empty(char *line, t_struct *minish);
int			is_variable_char(char c);
char		**interpret_args(char *line, char	**tab_arg, t_struct *minish);
int			len_arg(char *line, t_struct *minish);
int			len_double_quotes(char *line, t_struct *minish);
int			len_sig_error(t_struct *minish);
int			len_simple_quote(char *line, t_struct *minish);
int			len_variable(char *line, t_struct *minish);
int			parsing(char *line, t_struct *minish);
int			pass_arg(char *line, t_struct *minish);
int			pass_arg_count(char *line, t_struct *minish);
int			pass_quotes(char *line);
int			pass_redir(char *line, t_struct *minish);
int			pass_redir_hd(char *line, t_struct *minish);
int			pass_variable(char *line);
void		print_list(t_list_arg *list);
void		print_list_hd(t_list_hd *list);
int			recup_args(char *line, t_struct *minishell);
char		*recup_echo(char **args, t_struct *minish);
t_struct	*recup_here_doc_end(char *line, t_struct *minish);
char		*recup_name(char *args);
int			recup_pipe(char *line, t_struct *minishell);
int			recup_pipe2(char *line, t_struct *minish, int i);
char		**recup_redir(char *line, t_struct *minish);
void		redirections(t_list_arg *args, t_struct *minish);
t_list_arg	*reverse_list(t_list_arg *list);
t_list_hd	*reverse_list_hd(t_list_hd *list);
char		**sep_and_check_args(t_args *arg, t_struct *minish);

#endif
