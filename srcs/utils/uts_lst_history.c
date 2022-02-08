/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_lst_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:37:38 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/08 11:45:17 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_history(t_his *stack)
{
	t_his	*tmp;

	if (!stack)
		return ;
	while (stack != NULL)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp);
	}
	free(stack);
}

static t_his	*new_var(char *str, int nbr_cmd)
{
	t_his	*elem;

	elem = malloc(sizeof(t_his));
	if (!elem)
		return (NULL);
	elem->nbr = nbr_cmd;
	elem->cmd = str;
	elem->next = NULL;
	return (elem);
}

void	add_cmd_history(t_his **stack, char *cmd)
{
	int		nbr;
	t_his	*first;

	nbr = 1;
	if (!(*stack))
	{
		*stack = new_var(cmd, nbr);
		first = *stack;
	}
	else
	{
		first = *stack;
		while ((*stack)->next)
		{
			*stack = (*stack)->next;
			nbr++;
		}
		(*stack)->next = new_var(cmd, nbr);
	}
	*stack = first;
}
