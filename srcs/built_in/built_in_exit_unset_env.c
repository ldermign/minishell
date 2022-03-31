/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit_unset_env.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:19:41 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/31 10:00:41 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	nbr_only(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (!ft_is_digit(str[i]) && str[i] != '-')
// 			return (EXIT_FAILURE);
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }

static int	len_tab(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i])
		i++;
	return (i);
}

static int	no_alpha(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || str[i] == '-')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	built_in_exit(t_struct *ms, char **cmd, char *prompt)
{
	if (ms->parsing.nb_pipe == 0)
		printf("exit\n");
	if (cmd[1] != NULL)
	{
		g_sig_error = ft_atoi(cmd[1]);
		if (no_alpha(cmd[1]) == EXIT_FAILURE || ft_strlen(cmd[1]) >= 20)
		{
			fprintf(stderr, "minishell: exit: %s: numeric argument required\n", cmd[1]);
			g_sig_error = 2;
		}
	}
	else if (len_tab(cmd) > 2)
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		g_sig_error = 1;
		return (EXIT_SUCCESS);
	}
	if (ms->parsing.nb_pipe != 0)
		return (EXIT_SUCCESS);
	ft_free_tab(cmd);
	free(prompt);
	exit (g_sig_error);
	return (EXIT_SUCCESS);
}

int	built_in_unset(t_env *env, t_args *cmd)
{
	int	i;
	int	ret;

	i = 1;
	while (cmd->arg_to_pass[i])
	{
		ret = check_if_variable_already_exist(env->env_ms, cmd->arg_to_pass[i]);
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
