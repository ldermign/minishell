/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_fcts.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:50:38 by ldermign          #+#    #+#             */
/*   Updated: 2022/01/16 19:41:04 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FCTS_H
# define MINISHELL_FCTS_H

/*
**	START
*/

int	get_prompt(char *prompt, t_env *env);

/*
**	BUILT-IN
*/

void start_built_in(char *prompt, t_env *env);
int	recup_var_envs(char **env, t_env *cpy_env);

/*
**	UTILS
*/

char	**get_cmd_and_args_split(char *str);

/*
**	TEMPORAIRE
*/

void	print_tab_char(char **tabl);

#endif