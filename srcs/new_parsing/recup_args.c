/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:33:48 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/16 00:13:20 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	recup_pipe2(char *line, t_struct *minishell, int i)
{
	int		j;
	char	*str;

	str = malloc(sizeof(char) * i + 1);
	if (str == NULL)
	{
		printf("error malloc\n");
		minishell->parsing.error = 1;
		return (-2);
	}
	j = i;
	str[i] = '\0';
	i--;
	while (i >= 0)
	{
		str[i] = line[minishell->parsing.i_line + i];
		i--;
	}
	minishell->parsing.i_line += j;
	insertion(minishell->args, str);
	minishell->parsing.i_line++;
	return (i);
}

int	recup_pipe(char *line, t_struct *minishell)
{
	int		i;

	while (line[minishell->parsing.i_line])
	{
		i = 0;
		minishell->parsing.nb_pipe++;
		while (line[minishell->parsing.i_line + i]
			&& line[minishell->parsing.i_line + i] != '|')
			i++;
		if (recup_pipe2(line, minishell, i) == -2)
			return (-1);
	}
	return (0);
}

// static int	count_args(t_struct *minishell)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (minishell->args->first->arg[j] == ' ')
// 		j++;
	
// 	return (i);
// }

// static int	fill_args(t_struct *minishell)
// {
// 	int	i;

// 	i = 0;
// 	return (0);
// }

// static int	check_args(t_struct *minishell)
// {
// 	int	i;

// 	i = 0;
// 	return (0);
// }

static int	sep_and_check_args(t_struct *minishell)
{
	int	i;

	i = 0;
	// i = count_args(minishell);
	// if (i == -1)
		// return (-1);
	// minishell->args->tab_args = malloc(sizeof(char *) * i + 1);
	minishell->args->first->tab_args = ft_split(minishell->args->first->arg, ' ');
	if (minishell->args->first->tab_args == NULL)
	{
		printf("error malloc\n");
		minishell->parsing.error = 1;
		return (-1);
	}
	while (minishell->args->first->tab_args[i] != NULL)
	{
		printf("tab[%i] = [%s]\n", i, minishell->args->first->tab_args[i]);
		i++;
	}
	// if (fill_args(minishell) == -1)
	// 	return (-1);
	// if (check_args(minishell) == -1)
	// 	return (-1);
	return (0);
}

int	recup_args(char *line, t_struct *minishell)
{
	t_args	*tmp;

	if (recup_pipe(line, minishell) == -1)
		return (-1);
	tmp = minishell->args->first;
	while (minishell->args->first != NULL)
	{
		printf("\n\n");
		if (sep_and_check_args(minishell) == -1)
		{
			minishell->args->first = tmp;
			printf("error\n");
			return (-1);
		}
		minishell->args->first = minishell->args->first->next;
	}
	minishell->args->first = tmp;
	return (0);
}
