/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:48:39 by ldermign          #+#    #+#             */
/*   Updated: 2022/01/21 23:26:03 by ldermign         ###   ########.fr       */
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
	char		*rel;	// cheminn relatif du minishell
	t_env_ms	*env_ms;
}	t_env;

typedef	struct s_parsing
{
	int		i_line;
	int		echo;
	int		cd;
	int		pwd;
	int		export;
	int		unset;
	int		env;
	int		exit;
	char	*ret_error;
	char	*result;
	char	*fd;
	int		simple_quotes;
	int		double_quotes;
	int		option;
}	t_parsing;

#endif