/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:26:39 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/21 09:22:08 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int			len_tab;
	int			len_name;
	char		**copy;

	if (*env == NULL)
		return (EXIT_SUCCESS);
	len_tab = size_env(*env);
	copy = copy_env_in_tab_char(*env, len_tab);
	i = 0;
	while (i < len_tab - 1)
	{
		if ((ft_strcmp(copy[i], copy[i + 1])) > 0)
			swap(copy, &i);
		else
			i++;
	}
	i = 0;
	while (i < len_tab)
	{
		len_name = 0;
		while (copy[i][len_name] && copy[i][len_name] != '=')
			len_name++;
		write(1, "export ", 8);
		write(1, copy[i], len_name);
		if (copy[i][len_name])
		{
			write(1, "=\"", 2);
			len_name++;
			if (copy[i][len_name])
				write(1, &copy[i][len_name], ft_strlen(copy[i]) - len_name);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
	ft_free_tab(copy);
	return (EXIT_SUCCESS);
}

int	equal_in_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	built_in_export(t_args *cmd, t_env_ms **env)
{
	t_it	it;
	char	*str;

	init_struct_it(&it);
	if (cmd->arg_to_pass[1] == NULL)
		return (print_in_alphabetical_order(env));
	it.i = 1;
	while (cmd->arg_to_pass[it.i])
	{
		it.add = light_parse_export(cmd->arg_to_pass[it.i]);
		if (it.add != -1)
		{
			it.equal = equal_in_var(cmd->arg_to_pass[it.i]);
			it.pos = check_if_variable_already_exist(*env, cmd->arg_to_pass[it.i]);
			it.len = size_variable(cmd->arg_to_pass[it.i], it.add, it.pos);
			if (it.add == 1 && it.pos != -1)
				str = ft_strjoin(get_variable_with_pos(*env, it.pos),
						get_good_variable(cmd->arg_to_pass[it.i], it.len, it.add, it.pos));
			else
				str = get_good_variable(cmd->arg_to_pass[it.i], it.len, it.add, it.pos);
			if (it.pos == -1)
				add_var_env_minishell(env, str);
			else if (it.pos != -1 && it.equal != -1)
				change_var_env_minishell(*env, str, it.pos);
		}
		it.i++;
	}
	return (EXIT_SUCCESS);
}
