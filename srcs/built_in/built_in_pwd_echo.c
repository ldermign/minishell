/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd_cd_echo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:19:57 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/30 14:40:41 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in_pwd()
{
	char	actual_path[PATH_MAX];

	if (getcwd(actual_path, sizeof(actual_path)) != NULL)
	{
		write(1, actual_path, ft_strlen(actual_path));
		write(1, "\n", 1);
		g_sig_error = 0;
	}
	else
		g_sig_error = 127;
	return (g_sig_error);
}

int	built_in_echo(t_struct *ms)
{
	char	*sig;
	int		len;

	sig = 0;
	len = ft_strlen(ms->parsing.result);
	if (write(1, ms->parsing.result, len) == -1)
	{
		free(ms->parsing.result);
		fprintf(stderr, "echo: write error: No space left on device\n"); // ca marche pas du tout
		return (EXIT_FAILURE);
	}
	if (ms->parsing.option != 1)
		write(1, "\n", 1);
	free(ms->parsing.result);
	g_sig_error = 0;
	return (g_sig_error);
}
