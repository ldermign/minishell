/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_start_list_var_env_ms.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:26:10 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/31 11:27:37 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_ms	*new_var(char *str)
{
	t_env_ms	*elem;

	elem = malloc(sizeof(t_env_ms));
	if (!elem)
		return (NULL);
	elem->var = ft_strdup(str);
	elem->next = NULL;
	return (elem);
}

void	supp_var_env_ms(t_env_ms **stack, int pos)
{
	int			i;
	t_env_ms	*before;
	t_env_ms	*first;

	i = 0;
	first = *stack;
	before = *stack;
	while (*stack && i < pos)
	{
		before = *stack;
		*stack = (*stack)->next;
		i++;
	}
	if (first == *stack)
		first = (*stack)->next;
	else
		before->next = (*stack)->next;
	free((*stack)->var);
	free(*stack);
	*stack = first;
}

void	add_var_env_minishell(t_env_ms **stack, char *str_var)
{
	t_env_ms	*first;

	if (!(*stack))
	{
		*stack = new_var(str_var);
		first = *stack;
	}
	else
	{
		first = *stack;
		while ((*stack)->next)
			*stack = (*stack)->next;
		(*stack)->next = new_var(str_var);
	}
	*stack = first;
}
