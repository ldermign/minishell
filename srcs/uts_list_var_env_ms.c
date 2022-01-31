/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_list_var_env_ms.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 23:31:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/01/25 13:27:17 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_ms	*new_var(char *str)
{
	t_env_ms	*elem;

	elem = malloc(sizeof(t_env_ms));
	if (!elem)
		return (NULL);
	elem->var = str;
	elem->next = NULL;
	return (elem);
}

void	supp_var_env_ms(t_env_ms **stack, char *var)
{
	t_env_ms	*first;
	t_env_ms	*ret;

	first = *stack;
	ret = *stack;
	if (ft_pos_strstr((*stack)->var, var) != -1)
	{
		*stack = (*stack)->next;
		free(ret);
		return ;
	}
	while (*stack && ft_pos_strstr((*stack)->var, var) == -1)
	{
		ret = *stack;
		*stack = (*stack)->next;
	}
	ret->next = (*stack)->next;
	free(*stack);
	*stack = first;
}

int	search_for_var_in_env(t_env_ms **stack, char *var)
{
	t_env_ms	*first;

	first = *stack;
	while (*stack)
	{
		if (ft_pos_strstr((*stack)->var, var) != -1)
		{
			*stack = first;
			return (1);
		}
		*stack = (*stack)->next;
	}
	*stack = first;
	return (-1);
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