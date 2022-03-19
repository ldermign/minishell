/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:26:39 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/19 19:20:43 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env_in_tab_char(t_env_ms **ms)
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
		if (ft_pos_strstr((*ms)->var, "=") == -1)
		{
			copy[it.i] = malloc(sizeof(char) * ft_strlen((*ms)->var) + 1);
			while ((*ms)->var[it.j])
			{
				copy[it.i][it.k] = (*ms)->var[it.j];
				it.j++;
				it.k++;
			}
		}
		else
		{
			copy[it.i] = malloc(sizeof(char) * ft_strlen((*ms)->var) + 3);
			if (copy[it.i] == NULL)
				return (NULL);
			while ((*ms)->var[it.j])
			{
				if (it.ret == 0
					&& (*ms)->var[it.j - 1] && (*ms)->var[it.j - 1] == '=')
				{
					copy[it.i][it.k] = '"';
					it.k++;
					it.ret = 1;
				}
				copy[it.i][it.k] = (*ms)->var[it.j];
				it.j++;
				it.k++;
			}
			if (it.ret == 0)
			{
				copy[it.i][it.k] = '"';
				it.k++;
			}
			copy[it.i][it.k] = '"';
			it.k++;
		}
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
		it.bin = light_parse_export(cmd->arg_to_pass[it.i]);
		if (it.bin != -1)
		{
			it.equal = equal_in_var(cmd->arg_to_pass[it.i]);
			it.pos = check_if_variable_already_exist(*env, cmd->arg_to_pass[it.i]);
			it.len = size_variable(cmd->arg_to_pass[it.i], it.bin, it.pos);
			if (it.bin == 1 && it.pos != -1)
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


/*

si on a deja

aa="merde"
 et qu'on fait

export aa

ca ne change rien
a partir du egal, on change

*/