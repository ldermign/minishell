/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:53:30 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/18 22:58:45 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char *line, t_struct *minish)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		i += pass_arg_count(&line[i], minish);
		if (minish->parsing.error == 1)
			return (-1);
	}
	return (i);
}

// int	fill_arg2(char *line, char *str)
// {
	
// }

int	fill_arg(char *line, char *str, t_struct *minish)
{
	int	i;
	int	j;

	i = 0;
	j = len_arg(line, minish);
	(void)str;
	// str = malloc(sizeof(char) * j + 1);
	// if (str == NULL)
	// 	return (error_malloc(minish));
	// str[j] = '\0';
	// i += fill_arg2(line, str);
	return (i);
}

int	interpret_args(char *line, char	**tab, t_struct *minish)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		fill_arg(&line[i], tab[j], minish);
		i += pass_arg_count(&line[i], minish);
		if (minish->parsing.error == 1)
			return (-1);
		j++;
	}
	return (0);
}

int	sep_and_check_args(t_args *arg, t_struct *minish)
{
	int	i;
	int	j;

	j = 0;
	count_args(arg->command, minish);
	if (minish->parsing.error = 1)
		return (-1);
	i = minish->parsing.nb_arg;
	// printf("nombre d arguments = %d\n", minish->parsing.nb_arg);
	arg->arg_to_pass = malloc(sizeof(char *) * i + 1);
	if (arg->arg_to_pass == NULL)
		return (error_malloc(minish));
	arg->arg_to_pass[i] = NULL;
	while (j < i)
	{
		if (interpret_args(arg, minish) == -1)
			return (-1);
		j++;
	}
	free(arg->arg_to_pass);
	return (0);
}

/*

compte le nombre d arguments		//
malloc char* * nombre d arguments	//
calcule longueur argument			//
malloc char * longueur argument		//
rempli argument						//

passe char** args a liena 			//

pipes?								//

*/
