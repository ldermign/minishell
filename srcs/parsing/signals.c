/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 00:19:51 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/06 21:15:53 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	handle_signal_child(int sig)
{
	if (sig == SIGQUIT)
	{
		g_sig_error = 131;
		write(1, "Quit (core dumped)\n", 19);
		rl_on_new_line();
		rl_replace_line("", 0);
		// rl_redisplay();
		// exit (0);
	}
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		// rl_redisplay();
		g_sig_error = 130;
	}
}

void	handle_signal(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig_error = 130;
}
