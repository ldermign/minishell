/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:26:39 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/16 11:32:45 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_lines(char **new, char *to_copy, t_it *it)
{
	if (ft_pos_strstr(to_copy, "=") == -1)
	{
		new[it->i] = malloc(sizeof(char) * ft_strlen(to_copy) + 3);
		while (to_copy[it->j])
		{
			if (it->ret == 0
				&& to_copy[it->j - 1] && to_copy[it->j - 1] == '=')
			{
				new[it->i][it->k] = '"';
				it->k++;
				it->ret = 1;
			}
			new[it->i][it->k] = to_copy[it->j];
			it->j++;
			it->k++;
		}
		new[it->i][it->k] = '"';
		it->k++;
	}
	else
	{
		new[it->i] = malloc(sizeof(char) * ft_strlen(to_copy) + 1);
		while (to_copy[it->j])
		{
			new[it->i][it->k] = to_copy[it->j];
			it->j++;
			it->k++;
		}
	}
}

static char	**copy_env_in_tab_char(t_env_ms **ms)
{
	t_it		it;
	t_env_ms	*first;
	char		**copy;

	init_struct_it(&it);
	first = *ms;
	copy = malloc(sizeof(char *) * size_env(ms) + 1);
	if (copy == NULL)
		return (NULL);
	while (*ms)
	{
		it.j = 0;
		it.k = 0;
		it.ret = 0;
		copy_lines(copy, (*ms)->var, &it);
		copy[it.i][it.k] = '\0';
		it.i++;
		*ms = (*ms)->next;
	}
	copy[it.i] = NULL;
	*ms = first;
	return (copy);
}

static void swap(char **copy_env, int *i)
{
	char		*swap;

	swap = copy_env[*i];
	copy_env[*i] = copy_env[*i + 1];
	copy_env[*i + 1] = swap;
	*i = 0;
}

static int	print_in_alphabetical_order(t_env_ms **env)
{
	int			i;
	int			len;
	char		**copy;

	copy = copy_env_in_tab_char(env);
	i = 0;
	len = size_env(env);
	while (i < len - 1)
	{
		if ((ft_strcmp(copy[i], copy[i + 1])) > 0)
			swap(copy, &i);
		else
			i++;
	}
	i = 0;
	while (i < len)
	{
		write(1, "export ", 8);
		ft_putstr_fd(copy[i], 1);
		write(1, "\n", 1);
		i++;
	}
	ft_free_tab(copy);
	return (EXIT_SUCCESS);
}

int	built_in_export(t_env_ms **env, char *prompt, char *alpha)
{
	t_it	it;
	char	*str;

	init_struct_it(&it);
	if (alpha == NULL)
		return (print_in_alphabetical_order(env));
	it.i = 6;
	it.add = light_parse_export(&prompt[it.i]);
	if (it.add == -1)
		return (EXIT_FAILURE);
	while (prompt[it.i] == ' ')
		it.i++;
	it.pos = check_if_variable_already_exist(env, &prompt[it.i]);
	it.len = size_variable(&prompt[it.i], it.add, it.pos);
	if (it.add == 1 && it.pos != -1)
		str = ft_strjoin(get_variable_with_pos(env, it.pos),
				get_good_variable(&prompt[it.i], it.len, it.add, it.pos));
	else
		str = get_good_variable(&prompt[it.i], it.len, it.add, it.pos);
	if (it.pos == -1)
		add_var_env_minishell(env, str);
	else
		change_var_env_minishell(env, str, it.pos);
	return (EXIT_SUCCESS);
}
