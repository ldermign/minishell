/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:38:11 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/31 11:14:34 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_first(char *args)
{
	if (ft_pos_strstr(args, ">") != -1 || ft_pos_strstr(args, "<") != -1
		|| ft_pos_strstr(args, ">>") != -1 || ft_pos_strstr(args, "<<") != -1)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	is_redir(char **args, char *str)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_pos_strstr(args[i], str) != -1)
			return (1);
		i++;
	}
	return (0);
}

int	max(int nb1, int nb2)
{
	if (nb1 > nb2)
		return (nb1);
	return (nb2);
}

int	last_right(char *str)
{
	int	i;
	int	ret_r;
	int	ret_rr;

	i = 0;
	ret_r = -1;
	ret_rr = -1;
	while (str[i])
	{
		if (str[i] == '>')
		{
			i++;
			if (str[i] && str[i] == '>')
				ret_rr = i;
			else
				ret_r = i;
		}
		i++;
	}
	if (ret_r == -1 && ret_rr == -1)
		return (-1);
	if (ret_r > ret_rr)
		return (1);
	return (3);
}

int	last_left(char *str)
{
	int	i;
	int	ret_l;
	int	ret_ll;

	i = 0;
	ret_l = -1;
	ret_ll = -1;
	while (str[i])
	{
		if (str[i] == '<')
		{
			i++;
			if (str[i] && str[i] == '<')
				ret_ll = i;
			else
				ret_l = i;
		}
		i++;
	}
	if (ret_l == -1 && ret_ll == -1)
		return (-1);
	if (ret_l > ret_ll)
		return (2);
	return (4);
}
