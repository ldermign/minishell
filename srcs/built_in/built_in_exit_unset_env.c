/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit_unset_env.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:19:41 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/23 11:01:25 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	nbr_only(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_digit(str[i]) && str[i] != '-')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	len_tab(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i])
		i++;
	return (i);
}

void	built_in_exit(t_env *env, char **cmd, char *prompt)
{
	int	nbr;

	nbr = 0;
	printf("exit\n");
	if (len_tab(cmd) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		sig_error(NULL, 2);
	}
	if (cmd[1] != NULL)
	{
		nbr = ft_atol(cmd[1]);
		sig_error(NULL, ft_atoi(cmd[1]));
		if (nbr_only(cmd[1]) == EXIT_FAILURE
			|| ft_strlen(cmd[1]) > 20)
		{
			printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
			sig_error(NULL, 2);
		}
	}
	free_lst(env->env_ms);
	ft_free_tab(cmd);
	// ft_free_tab(env->env_bash); // il me dit qu'il faut pas free parce que j'ai pas alloue mais si ouesh...
	// free(env->rel); faut l'allouer d'abord en fait....
	free(prompt);
	exit (0);
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
	return (EXIT_SUCCESS);
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
	return (EXIT_SUCCESS);
}
