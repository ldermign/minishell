/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:26:39 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/31 14:31:13 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap(char **copy_env, int len)
{
	int		i;
	char	*swap;

	i = 0;
	while (i < len - 1)
	{
		if ((ft_strcmp(copy_env[i], copy_env[i + 1])) > 0)
		{
			swap = copy_env[i];
			copy_env[i] = copy_env[i + 1];
			copy_env[i + 1] = swap;
			i = 0;
		}
		else
			i++;
	}
}

char	**copy_env_in_tab_char(t_env_ms *ms, int size_tab)
{
	t_it		it;
	char		**copy;

	init_struct_it(&it);
	copy = malloc(sizeof(char *) * (size_tab + 1));
	if (copy == NULL)
		return (NULL);
	while (ms)
	{
		it.j = 0;
		it.k = 0;
		copy[it.i] = malloc(sizeof(char) * ft_strlen(ms->var) + 1);
		while (ms->var[it.j])
		{
			copy[it.i][it.k] = ms->var[it.j];
			it.j++;
			it.k++;
		}
		copy[it.i][it.k] = '\0';
		it.i++;
		ms = ms->next;
	}
	copy[it.i] = NULL;
	return (copy);
}

int	export_print_in_alphabetical_order(t_env_ms **env)
{
	t_it		it;
	char		**copy;

	if (*env == NULL)
		return (EXIT_SUCCESS);
	init_struct_it(&it);
	it.len = size_env(*env);
	copy = copy_env_in_tab_char(*env, it.len);
	swap(copy, it.len);
	while (it.i < it.len)
	{
		it.tmp1 = get_str_export(copy[it.i]);
		write(1, it.tmp1, ft_strlen(it.tmp1));
		free(it.tmp1);
		it.i++;
	}
	ft_free_tab(copy);
	return (EXIT_SUCCESS);
}

static char	*add_new_str_to_old(t_env_ms *env, char *cmds, t_it *it)
{
	char	*str;

	str = NULL;
	it->tmp1 = get_var_with_pos(env, it->pos);
	it->tmp2 = get_good_var(cmds, it->len, it->add, it->pos);
	str = ft_strjoin(it->tmp1, it->tmp2);
	free(it->tmp1);
	free(it->tmp2);
	return (str);
}

int	built_in_export(char **cmd, t_env_ms **env)
{
	t_it	it;

	init_struct_it(&it);
	it.i = 1;
	while (cmd[it.i])
	{
		it.add = light_parse_export(cmd[it.i]);
		if (it.add != -1)
		{
			it.pos = check_if_variable_exist(*env,
					cmd[it.i]);
			it.len = size_variable(cmd[it.i], it.add, it.pos);
			if (it.add == 1 && it.pos != -1)
				it.str = add_new_str_to_old(*env, cmd[it.i], &it);
			else
				it.str = get_good_var(cmd[it.i], it.len, it.add, it.pos);
			if (it.pos == -1)
				add_var_env_minishell(env, it.str);
			else if (it.pos != -1 && ft_int_strchr(cmd[it.i], '=') == 1)
				change_var_env_minishell(*env, it.str, it.pos);
			free(it.str);
		}
		it.i++;
	}
	return (EXIT_SUCCESS);
}
