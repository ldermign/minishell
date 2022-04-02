/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:48:39 by ldermign          #+#    #+#             */
/*   Updated: 2022/04/02 15:32:48 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

typedef struct s_env_minishell
{
	char					*var;
	struct s_env_minishell	*next;
}	t_env_ms;

typedef struct s_environnement
{
	t_env_ms	*env_ms;
}	t_env;

typedef struct s_here_doc
{
	char				*here_doc;
	struct s_here_doc	*next;
}	t_here_doc;

typedef struct s_list_hd
{
	t_here_doc	*first;
}	t_list_hd;

typedef struct s_args
{
	t_list_hd		*here_doc;
	char			**args_here_doc;
	char			**redir;
	char			*command;
	char			**arg_to_pass;
	struct s_args	*next;
}	t_args;

/*
	redir		->	recup toutes les redirections
	command		->	ligne de commande entre pipe
	arg_to_pass	->	arguments a donner aux fonction exec
*/

typedef struct s_list_arg
{
	t_args	*first;
}	t_list_arg;

typedef struct s_parsing
{
	int		i_line;
	int		error;
	int		nb_arg;
	int		len_arg;
	int		fill_arg;
	int		option;
	int		nb_pipe;
	int		quotes;
	char	*result;
}	t_parsing;

typedef struct s_redirection_std
{
	int		fd_to_read;
	int		fd_to_write;
	int		last_right;
	int		last_left;
	int		last;
	int		which;
	int		right;
	int		dbl_r;
	int		left;
	int		dbl_l;
	int		both;
	char	*name_file;
}	t_red_std;

typedef struct s_execute
{
	char	**new_env;
	char	**paths;
	char	*str_path;
}	t_execute;

typedef struct s_iterator
{
	int		i;
	int		j;
	int		k;
	int		l;
	int		right;
	int		right_right;
	int		left;
	int		left_left;
	int		last;
	int		pos;
	int		add;
	int		ret;
	int		len;
	int		bin;
	int		equal;
	char	*tmp1;
	char	*tmp2;
	char	*str;
}	t_it;

typedef struct s_pipe
{
	int		pipe_tot;
	int		cmd_nbr;
	int		nbr_exec;
	int		fd0[2];
	int		fd1[2];
	int		fd_to_read;
	int		fd_to_write;
	pid_t	pid;
}	t_pipe;

typedef struct s_structure
{
	pid_t			pid;
	t_parsing		parsing;
	t_env			env;
	t_list_arg		*args;
	t_red_std		std;
	t_execute		exec;
	char			*prompt;
	t_pipe			*pipex;
	int				nbr_line;
}	t_struct;

#endif
