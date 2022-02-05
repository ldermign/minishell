/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit_export_unset.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:19:41 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/04 14:23:30 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_exit(t_env *env, char **cmd_args, char *prompt)
{
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
		printf("%s\n", stack->var);
		stack = stack->next;
	}
	return (EXIT_SUCCESS);
}
