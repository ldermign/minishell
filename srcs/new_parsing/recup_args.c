/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:33:48 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/13 21:52:58 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recup_args(char *line, t_struct *minishell)
{
	int	i;
	int	j;
	char	*str;

	while (line[minishell->parsing.i_line])
	{
		i = 0;
		while (line[minishell->parsing.i_line + i] && line[minishell->parsing.i_line + i] != '|')
			i++;
		str = malloc(sizeof(char) * i + 1);
		if (str == NULL)
		{
			printf("error malloc\n");
			minishell->parsing.error = 1;
			return (-1);
		}
		j = i;
		str[i] = '\0';
		i--;
		while (i >= 0)
		{
			str[i] = line[minishell->parsing.i_line + i];
			i--;
			printf("i = %d\n", i);
		}
		minishell->parsing.i_line += j;
		insertion(minishell->args, str);
		minishell->parsing.i_line++;
	}
	return (0);
}
