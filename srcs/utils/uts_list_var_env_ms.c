/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_list_var_env_ms.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 23:31:36 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/31 14:24:59 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	change_var_env_minishell(t_env_ms *minishell, char *str, int pos)
{
	int	i;

	i = 0;
	while (i < pos)
	{
		minishell = minishell->next;
		i++;
	}
	free(minishell->var);
	minishell->var = ft_strdup(str);
}

int	check_if_variable_exist(t_env_ms *msh, char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (msh)
	{
		while (str[i] && msh->var[i] && str[i] == msh->var[i])
		{
			if (msh->var[i] == '=' && str[i] == '=')
				return (ret);
			i++;
		}
		if ((str[i] == '\0' && msh->var[i] == '\0') || (str[i] == '='
				&& msh->var[i] == '\0') || (str[i] == '\0'
				&& msh->var[i] == '=') || (str[i] && str[i + 1] && str[i] == '+'
				&& str[i + 1] == '='
				&& msh->var[i] == '=') || (str[i] && str[i + 1] && str[i] == '+'
				&& str[i + 1] == '=' && msh->var[i] == '\0'))
			return (ret);
		ret++;
		i = 0;
		msh = msh->next;
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

char	*get_var_with_pos(t_env_ms *minishell, int pos)
{
	int			i;
	char		*tmp;

	i = 0;
	while (minishell && i < pos)
	{
		minishell = minishell->next;
		i++;
	}
	if (ft_int_strchr(minishell->var, '=') == 0)
		tmp = ft_strjoin(minishell->var, "=");
	else
		tmp = ft_strdup(minishell->var);
	return (tmp);
}
