/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:42:53 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/29 18:46:42 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_hd	*ctrl_d(char *str, t_list_hd *hd, int nbr_line)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	fprintf(stderr, "minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", nbr_line, str);
	g_sig_error = 0;
	free(str);
	return (hd);
}

void	ctrl_d_hd(char *str, int nb)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	fprintf(stderr, "minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", nb, str);
	g_sig_error = 0;
}

void	ctrl_d_main(t_struct *minish)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "exit\n", 5);
	ft_free_all(minish);
	exit(g_sig_error);
}
