/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 00:19:51 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/18 11:28:53 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	handle_signal_child(int sig)
{
	if (sig == SIGQUIT)
	{
		sig_error(NULL, 131);
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
		sig_error(NULL, 130);
	}
}

void	handle_signal(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	sig_error(NULL, 130);
}
