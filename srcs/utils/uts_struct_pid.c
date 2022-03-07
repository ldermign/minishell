/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_struct_pid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:06:28 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/07 14:14:07 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst_pid(t_pid *stack)
{
	t_pid	*tmp;

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

t_pid	*new_nbr(int nbr)
{
	t_pid	*elem;

	elem = malloc(sizeof(t_pid));
	if (!elem)
		return (NULL);
	elem->pid = nbr;
	elem->next = NULL;
	return (elem);
}

void	add_nbr_back(t_pid **stack, int nbr)
{
	t_pid	*ret;

	if (!(*stack))
	{
		*stack = new_nbr(nbr);
		ret = *stack;
	}
	else
	{
		ret = *stack;
		while ((*stack)->next)
			*stack = (*stack)->next;
		(*stack)->next = new_nbr(nbr);
	}
	*stack = ret;
}

void	add_nbr_front(t_pid **stack, int nbr)
{
	t_pid	*adrs_tmp;

	adrs_tmp = new_nbr(nbr);
	adrs_tmp->next = (*stack);
	*stack = adrs_tmp;
}