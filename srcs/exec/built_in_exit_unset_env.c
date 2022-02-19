/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit_unset_env.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:19:41 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/19 22:54:47 by ldermign         ###   ########.fr       */
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
	return (1);
}

void	built_in_exit(t_env *env, char **cmd_args, char *prompt)
{
	int	nbr;

	nbr = 0;
	printf("exit\n");
	if (len_tab(cmd_args) > 2)
	{
		printf("bash: exit: too many arguments\n");
		sig_error = 2;
	}
	if (cmd_args[1] != NULL)
	{
		nbr = ft_atol(cmd_args[1]);
		sig_error = ft_atoi(cmd_args[1]);
		if (nbr_only(cmd_args[1]) == EXIT_FAILURE
			|| ft_strlen(cmd_args[1]) > 20)
		{
			printf("bash: exit: %s: numeric argument required\n", cmd_args[1]);
			sig_error = 2;
		}
	}
	free_lst(env->env_ms);
	ft_free_tab(cmd_args);
	ft_free_tab(env->path);
	// ft_free_tab(env->env_bash); // il me dit qu'il faut pas free parce que j'ai pas alloue mais si ouesh...
	// free(env->rel); faut l'allouer d'abord en fait....
	free(prompt);
	exit (0);
}

int	built_in_unset(t_env *env, char **args)
{
	int	i;
	int	ret;

	i = 0;
	ret = check_if_variable_already_exist(&(env->env_ms), args[1]);
	if (ret != -1)
		supp_var_env_ms(&(env->env_ms), ret);
	return (EXIT_SUCCESS);
}

int	built_in_env(t_env_ms *stack)
{
	while (stack)
	{
		if (ft_pos_strstr(stack->var, "=") != -1)
			printf("%s\n", stack->var);
		stack = stack->next;
	}
	return (EXIT_SUCCESS);
}
