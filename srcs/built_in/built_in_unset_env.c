/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:19:41 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/31 15:08:58 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in_unset(t_env *env, t_args *cmd)
{
	int	i;
	int	ret;

	i = 1;
	while (cmd->arg_to_pass[i])
	{
		ret = check_if_variable_exist(env->env_ms, cmd->arg_to_pass[i]);
		if (ret != -1)
			supp_var_env_ms(&(env->env_ms), ret);
		i++;
	}
	g_sig_error = 0;
	return (g_sig_error);
}

int	built_in_env(t_env_ms *stack)
{
	while (stack)
	{
		if (ft_pos_strstr(stack->var, "=") != -1)
		{
			write(1, stack->var, ft_strlen(stack->var));
			write(1, "\n", 1);
		}
		stack = stack->next;
	}
	g_sig_error = 0;
	return (g_sig_error);
}
