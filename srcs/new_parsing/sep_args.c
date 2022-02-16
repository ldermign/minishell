/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:53:30 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/16 08:26:37 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pass_quotes(t_args *arg, t_struct *minish, int i)
{
	int	j;

	j = i;
	i++;
	if (arg->command[i] == arg->command[j])
		return (i + 1);
	while (arg->command[i] && arg->command[i] != arg->command[j])
		i++;
	if (arg->command[i] == '\0')
	{
		printf("error : open quotes\n");
		minish->parsing.error = 1;
		return (-1);
	}
	i++;
	return (i);
}

int	count_args(t_args *arg, t_struct *minish)
{
	int	i;
	int	j;	//	nombre d arguments

	i = 0;
	j = 0;
	while (arg->command[i])
	{
		while (arg->command[i] == ' ')
			i++;
		if (arg->command[i] == '>' || arg->command[i] == '<')
		{
			while (arg->command[i] && arg->command[i] != ' ')
				i++;
		}
		while (arg->command[i] && arg->command[i] != ' ')
		{
			if (arg->command[i] == 39 || arg->command[i] == 34)
			{
				// flemmeeeeee
			}
			i++;
	}
}

// int	count_args(t_args *arg, t_struct *minish)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (arg->command[i])
// 	{
// 		while (arg->command[i] == ' ')
// 			i++;
// 		if (arg->command[i] == '\0')
// 			return (j);
// 		if ((arg->command[i] == 39) || (arg->command[i] == 34))
// 			i += pass_quotes(arg, minish, i);
// 		if (i == -1)
// 			return (-1);
// 		else
// 		{
// 			while (arg->command[i] && arg->command[i] != ' ')
// 			{
// 				while (arg->command[i] && arg->command[i] != ' '
// 					&& arg->command[i] != 39 && arg->command[i] != 34)
// 					i++;
// 				if (arg->command[i] == 39 || arg->command[i] == 34)
// 					i += pass_quotes(arg, minish, i);
// 				if (i == -1)
// 					return (-1);
// 			}
// 		}
// 		j++;
// 	}
// 	return (j);
// }

// int	len_arg(char *str)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	return (j);
// }

// int	fill_arg(t_args *arg, t_struct *minish, int i)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	return (i);
// }

// int	interpret_args(t_args *arg, t_struct *minish)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (arg->command[i])
// 	{
// 		arg->arg_to_pass[j] = malloc(sizeof(char) * len_arg(&arg->command[i] + 1));
// 		if (arg->arg_to_pass[j] == NULL)
// 		{
// 			printf("error malloc\n");
// 			minish->parsing.error = 1;
// 			return (-1);
// 		}
// 		i += fill_arg(arg, minish, i);
// 		j++;
// 	}
// }

int	sep_and_check_args(t_args *arg, t_struct *minish)
{
	int	i;

	i = 0;
	i = count_args(arg, minish);
	printf("i = %d\n", i);
	// arg->arg_to_pass = malloc(sizeof(char *) * i + 1);
	// if (arg->arg_to_pass == NULL)
	// {
	// 	printf("error malloc\n");
	// 	minish->parsing.error = 1;
	// 	return (-1);
	// }
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
