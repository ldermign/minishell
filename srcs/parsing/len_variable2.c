/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_variable2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 00:58:03 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/27 19:40:17 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_dollar(t_struct *minish)
{
	char	*str;

	minish->pid = 546456;
	str = ft_itoa(minish->pid);
	minish->parsing.len_arg += ft_strlen(str);
	free(str);
	return (1);
}

int	len_sig_error(t_struct *minish)
{
	char	*str;

	str = ft_itoa(g_sig_error);
	minish->parsing.len_arg += ft_strlen(str);
	free(str);
	return (1);
}

int	fill_double_dollar(t_struct *minish, char *str)
{
	char	*pid;
	int		i;

	i = 0;
	pid = ft_itoa(minish->pid);
	while (pid[i])
	{
		str[minish->parsing.fill_arg] = pid[i];
		i++;
		minish->parsing.fill_arg++;
	}
	free(pid);
	return (1);
}

int	fill_sig_error(t_struct *minish, char *str)
{
	char	*sig;
	int		i;

	i = 0;
	sig = ft_itoa(g_sig_error);
	while (sig[i])
	{
		str[minish->parsing.fill_arg] = sig[i];
		i++;
		minish->parsing.fill_arg++;
	}
	free(sig);
	return (1);
}
