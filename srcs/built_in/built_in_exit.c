/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:06:45 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/31 16:39:11 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_tab(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i])
		i++;
	return (i);
}

static int	no_alpha(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || str[i] == '-')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	built_in_exit(t_struct *ms, char **cmd)
{
	if (ms->parsing.nb_pipe == 0)
		printf("exit\n");
	if (cmd[1] != NULL)
	{
		g_sig_error = ft_atoi(cmd[1]);
		if (no_alpha(cmd[1]) == EXIT_FAILURE || ft_strlen(cmd[1]) >= 20)
		{
			fprintf(stderr, "minishell: exit: %s: numeric argument required\n",
				cmd[1]);
			g_sig_error = 2;
		}
	}
	else if (len_tab(cmd) > 2)
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		g_sig_error = 1;
		return (EXIT_SUCCESS);
	}
	if (ms->parsing.nb_pipe != 0)
		return (EXIT_SUCCESS);
	free_list(ms->args);
	ft_free_all(ms);
	exit (g_sig_error);
	return (EXIT_SUCCESS);
}
