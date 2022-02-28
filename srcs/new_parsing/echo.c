/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 21:46:21 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/28 15:30:01 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_echo(char **args, int j)
{
	int	i;
	// int	j;
	int	k;

	i = 0;
	// j = 1;
	k = 0;
	while (args[j])
	{
		while (args[j][i])
		{
			i++;
			k++;
		}
		j++;
		i = 0;
	}
	return (k + j - 2);
}

char	*fill_echo(char **arg, int len, int j, t_struct *minish)
{
	char	*str;
	int		i;
	// int		j;
	int		k;

	i = 0;
	// j = 1;
	k = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
	{
		printf("error malloc\n");
		minish->parsing.error = 1;
		return (NULL);
	}
	str[len] = '\0';
	while (arg[j])
	{
		while (arg[j][i])
		{
			str[k] = arg[j][i];
			i++;
			k++;
		}
		if (arg[j + 1] != NULL)
		{
			str[k] = ' ';
			k++;
		}
		j++;
		i = 0;
	}
	// printf("recup echo = [%s]\n", str);
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
	printf("j = %d\n", j);
	i = len_echo(args, j);
	if (i < 0)
		i = 0;
	// printf("len echo = %d\n", i);
	str = fill_echo(args, i, j, minish);
	if (minish->parsing.error == 1)
		return (NULL);
	return (str);
}
