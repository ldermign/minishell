/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 21:46:21 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/22 23:48:51 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_echo(char **args)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 1;
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

char	*fill_echo(char **arg, int len, t_struct *minish)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 1;
	k = 0;
	str = malloc(sizeof(char) * len + 1);
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
	printf("recup echo = [%s]\n", str);
	return (str);
}

char	*recup_echo(char **args, t_struct *minish)
{
	int		i;
	char	*str;

	i = len_echo(args);
	if (i < 0)
		i = 0;
	printf("len echo = %d\n", i);
	str = fill_echo(args, i, minish);
	if (minish->parsing.error == 1)
		return (NULL);
	return (str);
}