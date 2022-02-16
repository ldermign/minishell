/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:33:48 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/16 03:43:16 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	recup_pipe2(char *line, t_struct *minish, int i)
{
	int		j;
	char	*str;

	str = malloc(sizeof(char) * i + 1);
	if (str == NULL)
	{
		printf("error malloc\n");
		minish->parsing.error = 1;
		return (-2);
	}
	j = i;
	str[i] = '\0';
	i--;
	while (i >= 0)
	{
		str[i] = line[minish->parsing.i_line + i];
		i--;
	}
	minish->parsing.i_line += j;
	insertion(minish->args, str);
	minish->parsing.i_line++;
	return (i);
}

int	recup_pipe(char *line, t_struct *minish)
{
	int		i;

	while (line[minish->parsing.i_line])
	{
		i = 0;
		minish->parsing.nb_pipe++;
		while (line[minish->parsing.i_line + i]
			&& line[minish->parsing.i_line + i] != '|')
			i++;
		if (recup_pipe2(line, minish, i) == -2)
			return (-1);
	}
	return (0);
}

static int	count_args(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i][0] == '<' || str[i][0] == '>')
			j += 0;
		else if (str[i][0] == 39 && str[i][1] == 39)
			j += 0;
		else if (str[i][0] == 34 && str[i][1] == 34)
			j += 0;
		else
			j++;
		i++;
	}
	return (j);
}

static int	interpret_args(t_struct *minish)
{
	int	i;

	i = count_args(minish->args->first->tab_args);
	printf("i = %d\n", i);
	// minish->args->first->arg_to_pass = malloc(sizeof(char *) * i + 1);
	// if (minish->args->first->arg_to_pass == NULL)
	// {
	// 	printf("error malloc\n");
	// 	minish->parsing.error = 1;
	// 	return (-1);
	// }
	// while (i > 0)
	// {
		
	// }
	return (0);
}

static int	sep_and_check_args(t_struct *minish)
{
	int	i;

	i = 0;
	minish->args->first->tab_args = ft_split(minish->args->first->whole_command, ' ');
	if (minish->args->first->tab_args == NULL)
	{
		printf("error malloc\n");
		minish->parsing.error = 1;
		return (-1);
	}
	// while (minish->args->first->tab_args[i] != NULL)
	// {
	// 	printf("tab[%i] = [%s]\n", i, minish->args->first->tab_args[i]);
	// 	i++;
	// }
	if (interpret_args(minish) == -1)
		return (-1);
	return (0);
}

int	recup_args(char *line, t_struct *minish)
{
	t_args	*tmp;

	if (recup_pipe(line, minish) == -1)
		return (-1);
	tmp = minish->args->first;
	while (minish->args->first != NULL)
	{
		printf("\n\n");
		// printf("arg = [%s]\n", minish->args->first->whole_command);
		if (sep_and_check_args(minish) == -1)
		{
			minish->args->first = tmp;
			printf("error\n");
			return (-1);
		}
		minish->args->first = minish->args->first->next;
	}
	minish->args->first = tmp;
	return (0);
}
