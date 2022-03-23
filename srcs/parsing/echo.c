/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 21:46:21 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/23 01:00:31 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_echo(char **args, int j)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (args[j])
	{
		while (args[j][i])
		{
			i++;
			k++;
		}
		if (args[j + 1] != NULL)
			k++;
		j++;
		i = 0;
	}
	return (k);
}

char	*fill_echo(char **arg, int len, int j, t_struct *minish)
{
	char	*str;
	int		i;
	int		k;

	k = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (error_malloc_null(minish));
	str[len] = '\0';
	while (arg[j])
	{
		i = 0;
		while (arg[j][i])
		{
			str[k] = arg[j][i];
			i++;
			k++;
		}
		if (arg[j + 1] != NULL)
			str[k++] = ' ';
		j++;
	}
	return (str);
}

int	is_option(char *str, t_struct *minish)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		if (str[i] == 'n')
		{
			while (str[i] == 'n')
				i++;
			if (str[i] == '\0')
			{
				minish->parsing.option = 1;
				return (1);
			}
		}
	}
	return (0);
}

int	check_if_option(char **args, t_struct *minish)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		if (is_option(args[i], minish) == 0)
			return (i);
		i++;
	}
	return (i);
}

char	*recup_echo(char **args, t_struct *minish)
{
	int		i;
	int		j;
	char	*str;

	j = check_if_option(args, minish);
	i = len_echo(args, j);
	if (i < 0)
		i = 0;
	str = fill_echo(args, i, j, minish);
	if (minish->parsing.error != 0)
		return (NULL);
	return (str);
}
