/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:53:30 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/28 14:40:12 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	check_option(char *line, t_struct *minish)
// {
// 	int	i;
// 	int	j;

// 	i = 2;
// 	j = 0;
// 	while (line[j] == ' ')
// 		j++;
// 	while (ft_strlen(&line[j]) > 1
// 		&& ft_memcmp("-n", &line[j], 2) == 0)
// 	{
// 		i = 2;
// 		while (line[j + i] == 'n')
// 			i++;
// 		if (line[j + i] != '\0'
// 			&& line[j + i] != ' ')
// 			return (j);
// 		minish->parsing.option = 1;
// 		j += i;
// 		while (line[j] == ' ')
// 			j++;
// 	}
// 	// printf("option : [%s]\n", &line[j]);
// 	return (j);
// }

int	count_args(char *line, t_struct *minish)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] == ' ')
		i++;
	// if (ft_memcmp(&line[i], "echo", 4) == 0
	// 	&& (line[i + 4] == '\0' || line[i + 4] == ' '))
	// {
	// 	i += 4;
	// 	minish->parsing.nb_arg++;
	// 	// if (line[i] != '\0' || line[i] == '<' || line[i] == '>')
	// 	// 	return (i);
	// 	// while (line[i] == ' ')
	// 	// 	i++;
	// 	// printf("option = [%s]\n", &line[i]);
	// 	i += check_option(&line[i], minish);
	// }
	// printf("apres echo = [%s]\n", &line[i]);
	while (line[i])
	{
		// printf("boucle = [%s]\n", &line[i]);
		i += pass_arg_count(&line[i], minish);
		if (minish->parsing.error == 1)
			return (-1);
	}
	return (i);
}

char	*fill_arg(char *line, char *str, t_struct *minish)
{
	len_arg(line, minish);
	if (minish->parsing.error == 1)
		return (NULL);
	// printf("len arg = %d\n", minish->parsing.len_arg);
	str = malloc(sizeof(char) * minish->parsing.len_arg + 1);
	if (str == NULL)
	{
		error_malloc(minish);
		return (NULL);
	}
	ft_bzero(str, minish->parsing.len_arg + 1);
	minish->parsing.i_line = fill_arg2(line, str, minish);
	return (str);
}

char	**interpret_args(char *line, char **tab_arg, t_struct *minish)
{

	int	i;
	int	j;

	i = 0;
	j = 0;
	minish->parsing.i_line = 0;
	while (line[i] && minish->parsing.nb_arg-- > 0)
	{
		// if (j == 1 && ft_memcmp(tab_arg[0], "echo", 4) == 0
		// 	&& (tab_arg[0][4] == '\0' || tab_arg[0][4] == ' '))
		// {
		// 	i += check_option(&line[i], minish);
		// 	while (line[i] == ' ')
		// 		i++;
		// 	if (line[i] == '\0')
		// 		return (tab_arg);
		// }
		// printf("line = [%s]\n", &line[i]);
		tab_arg[j] = fill_arg(&line[i], tab_arg[j], minish);
		i += minish->parsing.i_line;
		// i += pass_arg_count(&line[i], minish);
		// i += pass_arg(&line[i], minish);
		if (minish->parsing.error == 1)
			return (NULL);
		// printf("i = %d\n", i);
		// printf("arg[%d] = [%s]\n", j, tab_arg[j]);
		while (line[i] == ' ')
			i++;
		j++;
	}
	
	// printf("ok\n");
	// tab_arg[j] = NULL;
	// printf("ok\n");
	
	// i = 0;
	// while (tab_arg[i] != NULL)
	// {
	// 	printf("[%s]\n", tab_arg[i]);
	// 	printf("oui\n");
	// 	i++;
	// }
	return (tab_arg);
}

char	**sep_and_check_args(t_args *arg, t_struct *minish)
{
	int		i;
	char	**arg_to_pass;

	count_args(arg->command, minish);
	if (minish->parsing.error == 1)
		return (NULL);
	i = minish->parsing.nb_arg;
	// printf("nombre d arguments = %d\n", minish->parsing.nb_arg);
	if (i == 0)
		return (NULL);
	arg_to_pass = malloc(sizeof(char *) * (i + 1));
	if (arg_to_pass == NULL)
	{
		error_malloc(minish);
		return (NULL);
	}
	// printf("la i = %d\n", i);
	arg_to_pass[i] = NULL;	// >>>>> fait seg fault??
	// printf("aussi\n");
	arg_to_pass = interpret_args(arg->command, arg_to_pass, minish);
	if (minish->parsing.nb_arg != 0 && minish->parsing.error == 1)
	{
		free(arg_to_pass);
		return (NULL);
	}
	return (arg_to_pass);
}