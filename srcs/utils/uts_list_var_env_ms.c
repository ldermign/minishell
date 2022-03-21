/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_list_var_env_ms.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 23:31:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/21 10:44:58 by ldermign         ###   ########.fr       */
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

int	size_env(t_env_ms *minishell)
{
	int			len;

	len = 0;
	if (minishell == NULL)
		return (len);
	while (minishell)
	{
		minishell = minishell->next;
		len++;
	}
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

void	change_var_env_minishell(t_env_ms *minishell, char *str, int pos)
{
	int	i;

	i = 0;
	while (i < pos)
	{
		minishell = minishell->next;
		i++;
	}
	minishell->var = str;
}

int	check_if_variable_already_exist(t_env_ms *minishell, char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (minishell)
	{
		while (str[i] && minishell->var[i] && str[i] == minishell->var[i])
		{
			if (minishell->var[i] == '=' && str[i] == '=')
				return (ret);
			i++;
		}
		if ((str[i] == '\0' && minishell->var[i] == '\0')
			|| (str[i] == '=' && minishell->var[i] == '\0')
			|| (str[i] == '\0' && minishell->var[i] == '=')
			|| (str[i + 1] && str[i] == '+' && str[i + 1] == '=' && minishell->var[i] == '='))
			return (ret);
		ret++;
		i = 0;
		minishell = minishell->next;
	}
	return (-1);
}

char	*get_variable(t_env_ms *minishell, char *str)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = NULL;
	while (minishell)
	{
		while (str[i] && minishell->var[i] && str[i] == minishell->var[i])
			i++;
		if (str[i] == '\0' && minishell->var[i] == '=')
		{
			tmp = &(minishell->var[ft_strlen(str) + 1]);
			break ;
		}
		i = 0;
		minishell = minishell->next;
	}
	return (tmp);
}

char	*get_variable_with_pos(t_env_ms *minishell, int pos)
{
	int			i;
	char		*tmp;

	i = 0;
	while (minishell && i < pos)
	{
		minishell = minishell->next;
		i++;
	}
	tmp = minishell->var;
	return (tmp);
}
