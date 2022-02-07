/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:48:39 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/07 20:12:50 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

typedef struct	s_env_minishell
{
	char					*var;
	struct s_env_minishell	*next;
}	t_env_ms;


typedef struct	t_environnement
{
	char		**env_bash;	// env de bash
	char		**path;	// variable d'environnement PATH de bash
	char		*abs;	// chemin absolu du minishell
	// char		*rel;	// cheminn relatif du minishell -> utile ?
	t_env_ms	*env_ms;
}	t_env;

typedef	struct s_parsing
{
	int		i_line;
	int		error;
	int		red1;
	int		red2;
	char	*result;
	char	*file_redirection;
	int		option;
	int		pipe_fd[2];
}	t_parsing;

typedef struct t_structure
{
	t_parsing	parsing;
	t_env		env;
}	t_struct;

typedef struct t_iterator
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	len;
}	t_it;

#endif