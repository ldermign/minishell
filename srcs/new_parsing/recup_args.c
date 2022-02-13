/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:33:48 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/13 18:53:08 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recup_args(char *line, t_struct *minishell)
{
	int	i;
	char	*str;

		i = 0;
	while (line[minishell->parsing.i_line + i])
	{
		i = 0;
		while (line[minishell->parsing.i_line + i] && line[minishell->parsing.i_line + i] != '|')
		{
			i++;
		}
		str = malloc(sizeof(char) * i + 1);
		if (str == NULL)
		{
			printf("error malloc\n");
			minishell->parsing.error = 1;
			return (-1);
		}
		minishell->parsing.i_line += i;
		str[i] = '\0';
		i--;
		while (i > 0)
		{
			str[i] = line[minishell->parsing.i_line - i];
			i--;
		}
		insertion(minishell->args, str);
	}
	return (0);
}
