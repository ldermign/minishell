/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_list_var_env_ms.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 23:31:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/08 11:45:08 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst(t_env_ms *stack)
{
	t_env_ms	*tmp;

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

int	size_env(t_env_ms **minishell)
{
	int	len;
	t_env_ms	*first;

	len = 0;
	first = *minishell;
	while (*minishell)
	{
		*minishell = (*minishell)->next;
		len++;
	}
	*minishell = first;
	return (len);
}

static t_env_ms	*new_var(char *str)
{
	t_env_ms	*elem;

	elem = malloc(sizeof(t_env_ms));
	if (!elem)
		return (NULL);
	elem->var = str;
	elem->next = NULL;
	return (elem);
}

void	supp_var_env_ms(t_env_ms **stack, int pos)
{
	int			i;
	t_env_ms	*first;
	t_env_ms	*ret;

	i = 0;
	first = *stack;
	ret = *stack;
	while (*stack && i < pos)
	{
		ret = *stack;
		*stack = (*stack)->next;
		i++;
	}
	ret->next = (*stack)->next;
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

void	change_var_env_minishell(t_env_ms **minishell, char *str, int pos)
{
	int			i;
	t_env_ms	*first;

	i = 0;
	first = *minishell;
	while (i < pos)
	{
		*minishell = (*minishell)->next;
		i++;
	}
	(*minishell)->var = str;
	*minishell = first;
}

int	check_if_variable_already_exist(t_env_ms **minishell, char *str)
{
	int			i;
	int			ret;
	t_env_ms	*first;

	i = 0;
	ret = 0;
	first = *minishell;
	while (*minishell)
	{
		while (str[i] && (*minishell)->var[i] && str[i] == (*minishell)->var[i])
		{
			if ((str[i] == '=' && str[i] == '='))
			{
				*minishell = first;
				return (ret);
			}
			i++;
		}
		if (str[i] == '\0')
		{
			*minishell = first;
			return (ret);
		}
		ret++;
		i = 0;
		*minishell = (*minishell)->next;
	}
	*minishell = first;
	return (-1);
}

char	*get_variable(t_env_ms **minishell, char *str)
{
	int			i;
	char		*tmp;
	t_env_ms	*first;

	i = 0;
	tmp = NULL;
	first = *minishell;
	while (*minishell)
	{	
		while (str[i] && (*minishell)->var[i] && str[i] == (*minishell)->var[i])
			i++;
		if (str[i] == '\0')
		{
			tmp = &((*minishell)->var[ft_strlen(str) + 1]);
			break ;
		}
		i = 0;
		*minishell = (*minishell)->next;
	}
	*minishell = first;
	return (tmp);
}
