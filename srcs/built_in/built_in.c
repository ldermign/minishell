/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:19:48 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/26 16:58:22 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in(t_struct *ms, t_args *cmd)
{
	if (ft_memcmp(cmd->arg_to_pass[0], "cd", 3) == 0)
		return (built_in_cd(&(ms->env), cmd->arg_to_pass[1]));
	else if (ft_memcmp(cmd->arg_to_pass[0], "pwd", 4) == 0)
		return (built_in_pwd());
	else if (ft_memcmp(cmd->arg_to_pass[0], "env", 4) == 0)
		return (built_in_env(ms->env.env_ms));
	else if (ft_memcmp(cmd->arg_to_pass[0], "export", 7) == 0)
		return (built_in_export(cmd, &(ms->env.env_ms)));
	else if (ft_memcmp(cmd->arg_to_pass[0], "unset", 6) == 0)
		return (built_in_unset(&(ms->env), cmd));
	else if (ft_memcmp(cmd->arg_to_pass[0], "echo", 5) == 0)
	{
		ms->parsing.result = recup_echo(cmd->arg_to_pass, ms);
		return (built_in_echo(ms));
	}
	else if (ft_memcmp(cmd->arg_to_pass[0], "exit", 5) == 0)
		built_in_exit(&(ms->env), cmd->arg_to_pass, cmd->command);
	return (-1);
}
