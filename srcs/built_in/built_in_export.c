/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:26:39 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/23 16:07:19 by ldermign         ###   ########.fr       */
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

static void	swap(char **copy_env, int *i)
{
	char		*swap;

	swap = copy_env[*i];
	copy_env[*i] = copy_env[*i + 1];
	copy_env[*i + 1] = swap;
	*i = 0;
}

static void	get_export(char *new)
{
	new[0] = 'e';
	new[1] = 'x';
	new[2] = 'p';
	new[3] = 'o';
	new[4] = 'r';
	new[5] = 't';
	new[6] = ' ';
}

char	*get_str_export(char *str)
{
	int		i;
	int		j;
	int		len_tot;
	int		len_name;
	char	*new;

	len_tot = ft_strlen(str) + 3;
	if (ft_int_strchr(str, '=') == 0)
		len_tot -= 3;
	len_name = 0;
	while (str[len_name] && str[len_name] != '=')
			len_name++;
	new = malloc(sizeof(char) * (len_tot + 1));
	if (new == NULL)
		return (NULL);
	get_export(new);
	i = 7;
	len_name += 7;
	j = 0;
	while (i < len_name)
	{
		new[i] = str[j];
		i++;
		j++;
	}
	if (str[j])
	{
		new[i] = str[j];
		i++;
		j++;
		new[i] = '"';
		while (str[j])
		{
			i++;
			j++;
			new[i] = str[j];
		}
		new[i] = '"';
	}
	new[i] = '\0';
	return (new);
}

static int	print_in_alphabetical_order(t_env_ms **env)
{
	int			i;
	int			len_tab;
	int			len_name;
	char		**copy;
	char		*test;

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
		test = get_str_export(copy[i]);
		write(1, test, ft_strlen(test));
		// while (copy[i][len_name] && copy[i][len_name] != '=')
		// 	len_name++;
		// write(1, "export ", 8);
		// write(1, copy[i], len_name);
		// if (copy[i][len_name])
		// {
		// 	write(1, "=\"", 2);
		// 	len_name++;
		// 	if (copy[i][len_name])
		// 		write(1, &copy[i][len_name], ft_strlen(copy[i]) - len_name);
		// 	write(1, "\"", 1);
		// }
		// write(1, "\n", 1);
		// i++;
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
			it.pos = check_if_variable_already_exist(*env, cmd->arg_to_pass[it.i]);
			// printf("[%d][%s]\n", it.pos, get_variable_with_pos(*env, it.pos));
			// exit (0);
			it.len = size_variable(cmd->arg_to_pass[it.i], it.add, it.pos);
			if (it.add == 1 && it.pos != -1)
			{
				it.tmp1 = get_variable_with_pos(*env, it.pos);
				it.tmp2 = get_good_variable(cmd->arg_to_pass[it.i], it.len, it.add, it.pos);
				str = ft_strjoin(it.tmp1, it.tmp2);
				free(it.tmp1);
				free(it.tmp2);
			}
			else
				str = get_good_variable(cmd->arg_to_pass[it.i], it.len, it.add, it.pos);
			if (it.pos == -1)
				add_var_env_minishell(env, str);
			else if (it.pos != -1 && equal_in_var(cmd->arg_to_pass[it.i]) != -1)
				change_var_env_minishell(*env, str, it.pos);
		}
		it.i++;
	}
	return (EXIT_SUCCESS);
}
