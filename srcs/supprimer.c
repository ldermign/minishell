/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supprimer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 20:17:21 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/07 14:15:57 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tab_char(char **tabl)
{
	int	i;

	i = 0;
	printf(GREEN"--------------------\n");
	while (tabl[i] != NULL)
	{
		printf("Line %d = [%s]\n", i, tabl[i]);
		i++;
	}
	printf("Line %d = [%s]\n", i, tabl[i]);
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

void	print_struct_pid(t_pid **stack)
{
	t_pid	*first;

	first = *stack;
	if (*stack == NULL)
		exit (0);
	printf(GREY"__________\n");
	while (*stack != NULL)
	{
		printf("[ %d ]\n", (*stack)->pid);
		*stack = (*stack)->next;
	}
	printf("__________\n"NORMAL);
	*stack = first;
}