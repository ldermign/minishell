/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:33:48 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/16 07:18:12 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	recup_pipe2(char *line, t_struct *minish, int i)
{
	int		j;
	char	*str;

	str = malloc(sizeof(char) * i + 1);
	if (str == NULL)
	{
		printf("error malloc\n");
		minish->parsing.error = 1;
		return (-2);
	}
	j = i;
	str[i] = '\0';
	i--;
	while (i >= 0)
	{
		str[i] = line[minish->parsing.i_line + i];
		i--;
	}
	minish->parsing.i_line += j;
	insertion(minish->args, str);
	minish->parsing.i_line++;
	return (i);
}

int	recup_pipe(char *line, t_struct *minish)
{
	int		i;

	while (line[minish->parsing.i_line])
	{
		i = 0;
		minish->parsing.nb_pipe++;
		while (line[minish->parsing.i_line + i]
			&& line[minish->parsing.i_line + i] != '|')
			i++;
		if (recup_pipe2(line, minish, i) == -2)
			return (-1);
	}
	return (0);
}

int	recup_args(char *line, t_struct *minish)
{
	t_args	*tmp;

	if (recup_pipe(line, minish) == -1)
		return (-1);
	tmp = minish->args->first;
	while (minish->args->first != NULL)
	{
		printf("\n\n");
		// printf("arg = [%s]\n", minish->args->first->command);
		if (sep_and_check_args(minish->args->first, minish) == -1)
		{
			minish->args->first = tmp;
			printf("error\n");
			return (-1);
		}
		minish->args->first = minish->args->first->next;
	}
	minish->args->first = tmp;
	return (0);
}
