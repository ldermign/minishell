/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:48:39 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/05 21:32:16 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char		**env_bash;	// env de bash
	char		**path;		// variable d'environnement PATH de bash
	char		*abs;		// chemin absolu du minishell
	// char		*rel;		// cheminn relatif du minishell -> utile ?
	t_env_ms	*env_ms;
}	t_env;

typedef struct s_args
{
	char			**redir;
	char			*command;
	char			**arg_to_pass;
	struct s_args	*next;
}	t_args;

typedef struct s_pid
{
	pid_t			pid;
	struct s_pid	*next;
}	t_pid;

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
	int		which;
	int		right;
	int		dbl_r;
	int		left;
	int		dbl_l;
	int		both;
	char	*name_file;
}	t_red_std;

typedef struct s_structure
{
	pid_t			pid;
	t_parsing		parsing;
	t_env			env;
	t_list_arg		*args;
	t_red_std		std;
	char			*prompt;
	int				pipe_right;
	int				pipe_left;
}	t_struct;

typedef struct s_iterator
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	pos;
	int	add;
	int	ret;
	int	len;
}	t_it;

typedef struct s_pipe
{
	int		pipe;
	int		status;
	int		pipe_tot;
	int		pipe_nbr;
	int		pipe_left;
	int		pipe_right;
	int		cmd_nbr;
	int		fd1[2];
	int		fd2[2];
	pid_t	pid;
}	t_pipe;

#endif

/*
> 1
< 2
>> 3
<< 4
*/
