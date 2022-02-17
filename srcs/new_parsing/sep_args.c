/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:53:30 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/17 08:46:23 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pass_quotes(char *line, t_struct *minish)
{
	int	j;
	int	i;

	j = 0;
	i = 1;
	if (line[i] == line[j])
		return (i + 1);
	while (line[i] && line[i] != line[j])
		i++;
	i++;
	return (i);
}

int	pass_redir(char *line, t_struct *minish)
{
	int	i;

	i = 1;
	if (line[i] == line[0])
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|' || line[i] == '<' || line[i] == '>' || line[i] == '\0')
	{
		if (line[i] == '\0')
			printf("syntax error near unexpected token `newline'\n");
		else
			printf("syntax error near unexpected token `%c'\n", line[i]);
		minish->parsing.error = 1;
		return (-1);	
	}
	while (line[i] && line[i] != ' ')
		i++;
	return (i);
}

int	pass_variable(char *line, t_struct *minish)
{
	int	i;

	i = 1;
	while (line[i] && line[i] != 39 || line[i] != 34
		|| line[i] != '<' || line[i] != '>' || line[)
		i++;
	return (i - 1);
}

int	is_variable_char(char c)
{
	if (c == ' ' || c = 34 || c == 39 || c == '|' || c == '$' || c == '\0')
		return (1);
	return (0);
}

int	is_empty(char *line, t_struct *minish)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	if (line[i] == '$' && line[i + 1] == '{')
	{
		i += 2;
		while (is_variable_char(line[i]) == 0 && c != '}')
			i++;
		if (is_variable_char(line[i] == 1))
		{
			printf("${%c}: bad substitution\n", line[i]);
			parsing->error = 1;
			return (-1);
		}
		str = malloc(sizeof(char) * i - 1);
		if (str == NULL)
		{
			printf("error malloc\n");
			minish->parsing.error = 1;
			return (-1);
		}
		str[i - 1] = '\0';
		while (i > 1)
		{
			str[i - 2] = line[i]
			i--;
		}
	}
	else if ()
}

int	pass_arg_count(char *line, t_struct *minish)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '<' || line[i] == '>')
		return (pass_redir(line, minish));
	else if (line[i] == '\0')
		return (i);
	else if (line[i] == 39 || line[i] == 34 || line[i] == '$')
	{
		j = is_empty(&line[i], minish);
		if (j == 0)
			while (line[i] && line[i] != ' ')
				i++;
		return (i);
	}			
	minish->parsing.nb_arg++;
	while (line[i])
	{
		while (line[i] && line[i] != 39 && line[i] != 34
			&& line[i] != ' ' && line[i] != '$')
			i++;
		if (line[i] == 39 || line[i] == 34)
			i += pass_quotes(&line[i], minish);
		else if (line[i] == '$')
			i += pass_variable(&line[i], minish);
		else if (line[i] == '\0' || line[i] == ' ')
			return (i);
		if (minish->parsing.error == 1)
			return (-1);
		i++;
	}
	return (i);
}

int	count_args(char *line, t_struct *minish)
{
	int	i;
	int	j;	//	nombre d arguments

	i = 0;
	j = 0;
	while (line[i])
	{
		i += pass_arg_count(&line[i], minish);
		if (minish->parsing.error == 1)
			return (-1);
	}
}

int	sep_and_check_args(t_args *arg, t_struct *minish)
{
	int	i;

	i = 0;
	count_args(arg->command, minish);
	printf("i = %d\n", minish->parsing.nb_arg);
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
