/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:48:39 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/17 04:51:20 by ejahan           ###   ########.fr       */
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
	char		**env_bash;	// env de bash
	char		**path;	// variable d'environnement PATH de bash
	char		*abs;	// chemin absolu du minishell
	// char		*rel;	// cheminn relatif du minishell -> utile ?
	t_env_ms	*env_ms;
}	t_env;

typedef struct s_args
{
	char			**tab_args;	//	recup arguments pas changes
	char			**redir;	//	recup toutes les redirections
	char			*command;
	char			**arg_to_pass;	//	arguments a donner aux fonction exec
	struct s_args	*next;
}	t_args;

typedef struct s_list_arg
{
	t_args	*first;
}	t_list_arg;

typedef struct s_parsing
{
	int		i_line;
	int		error;
	int		red1;
	int		red2;
	int		nb_arg;
	int		option;
	int		nb_pipe;
	int		pipe_fd[2];
	char	*result;
	// char	*file_redirection;
}	t_parsing;

typedef struct s_structure
{
	t_parsing		parsing;
	t_parsing		*new_parsing;
	t_env			env;
	t_list_arg		*args;
}	t_struct;

typedef struct s_iterator
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	ret;
	int	len;
}	t_it;

#endif
