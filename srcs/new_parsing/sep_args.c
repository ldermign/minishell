/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:53:30 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/19 06:07:11 by ejahan           ###   ########.fr       */
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

int	fill_arg(char *line, char *str, t_struct *minish)
{
	len_arg(line, minish);
	str = malloc(sizeof(char) * minish->parsing.len_arg + 1);
	if (str == NULL)
		return (error_malloc(minish));
	ft_bzero(str, minish->parsing.len_arg + 1);
	fill_arg2(line, str, minish);
	// str[minish->parsing.fill_arg] = '\0';
	printf("str = [%s]\n", str);
	return (0);
}

int	interpret_args(char *line, char	**tab_arg, t_struct *minish)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		fill_arg(&line[i], tab_arg[j], minish);
		// printf("str = [%s]\n", tab_arg[j]);	// marche paaaaaaas
		i += pass_arg_count(&line[i], minish);
		if (minish->parsing.error == 1)
			return (-1);
		while (line[i] == ' ')
			i++;
		j++;
	}
	return (0);
}

int	sep_and_check_args(t_args *arg, t_struct *minish)
{
	int	i;

	count_args(arg->command, minish);
	if (minish->parsing.error == 1)
		return (-1);
	i = minish->parsing.nb_arg;
	printf("nombre d arguments = %d\n", minish->parsing.nb_arg);
	arg->arg_to_pass = malloc(sizeof(char *) * i + 1);
	if (arg->arg_to_pass == NULL)
		return (error_malloc(minish));
	arg->arg_to_pass[i] = NULL;
	if (interpret_args(arg->command, arg->arg_to_pass, minish) == -1)
	{
		free(arg->arg_to_pass);
		return (-1);
	}
	i = 0;
	while (arg->arg_to_pass[i] != NULL)
	{
		// printf("arg = [%s]\n", arg->arg_to_pass[i]);
		// printf("arg[%d]\n", i);
		// free(arg->arg_to_pass[i]);
		i++;
	}
	free(arg->arg_to_pass);	//	to delete
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
