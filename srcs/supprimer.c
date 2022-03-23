/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supprimer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 20:17:21 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/23 02:55:34 by ejahan           ###   ########.fr       */
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
		printf("[%d] = [%s]\n", i, tabl[i]);
		i++;
	}
	printf("--------------------\n"NORMAL);
}

void	print_env_ms(t_env_ms *stack)
{
	if (stack == NULL)
		exit (0);
	printf(GREY"_______________________________\n");
	while (stack != NULL)
	{
		printf("%s\n", stack->var);
		stack = stack->next;
	}
	printf("_______________________________\n"NORMAL);
}

void	print_stack_cmd(t_args *stack)
{
	if (stack == NULL)
		exit (0);
	printf(GREY"_______________________________\n");
	while (stack != NULL)
	{
		// print_tab_char(stack->redir);
		printf("command = %s\n", stack->command);
		print_tab_char(stack->arg_to_pass);
		stack = stack->next;
	}
	printf("_______________________________\n"NORMAL);
}
