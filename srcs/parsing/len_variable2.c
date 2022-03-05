/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_variable2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 00:58:03 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/05 01:11:12 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_dollar(t_struct *minish)
{
	minish->pid = 546456;
	minish->parsing.len_arg += ft_strlen(ft_itoa(minish->pid));
	return (1);
}

int	len_sig_error(t_struct *minish)
{
	minish->parsing.len_arg += ft_strlen(ft_itoa(sig_error));
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
	sig = ft_itoa(sig_error);
	while (sig[i])
	{
		str[minish->parsing.fill_arg] = sig[i];
		i++;
		minish->parsing.fill_arg++;
	}
	free(sig);
	return (1);
}
