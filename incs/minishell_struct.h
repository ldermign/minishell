/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:48:39 by ldermign          #+#    #+#             */
/*   Updated: 2022/01/18 15:59:16 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

typedef struct	t_environnement
{
	char	**env;
	char	**path;
	char	*abs;
	char	*rel;
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