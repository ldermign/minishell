/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supprimer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 20:17:21 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/10 20:06:08 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tab_char(char **tabl)
{
	int	i;

	i = 0;
	printf(GREEN"--------------------\n");
	while (tabl[i])
	{
		printf("Line %d = [%s]\n", i, tabl[i]);
		i++;
	}
	printf("--------------------\n"NORMAL);
}

void	print_env_ms(t_env_ms **stack)
{
	t_env_ms	*first;

	first = *stack;
	if (*stack == NULL)
		exit (0);
	printf(GREY"_______________________________\n");
	while (*stack != NULL)
	{
		printf("%s\n", (*stack)->var);
		*stack = (*stack)->next;
	}
	printf("_______________________________\n"NORMAL);
	*stack = first;
}
