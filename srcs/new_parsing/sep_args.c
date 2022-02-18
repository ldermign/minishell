/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:53:30 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/18 06:04:09 by ejahan           ###   ########.fr       */
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
		// printf("line = [%s]\narg = %d\n", &line[i], minish->parsing.nb_arg);
		i += pass_arg_count(&line[i], minish);
		if (minish->parsing.error == 1)
			return (-1);
		printf("line after = [%s]\narg = %d\n", &line[i], minish->parsing.nb_arg);
	}
	return (i);
}

int	sep_and_check_args(t_args *arg, t_struct *minish)
{
	int	i;

	i = 0;
	count_args(arg->command, minish);
	printf("nombre d arguments = %d\n", minish->parsing.nb_arg);
	// arg->arg_to_pass = malloc(sizeof(char *) * i + 1);
	// if (arg->arg_to_pass == NULL)
		// return (error_malloc(minish));
	// arg->arg_to_pass[i] = NULL;
	// if (interpret_args(arg, minish) == -1)
	// 	return (-1);
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
