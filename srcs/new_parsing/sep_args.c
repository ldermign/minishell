/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:53:30 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/18 05:10:54 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pass_quotes(char *line)
{
	int	j;
	int	i;

	j = 0;
	i = 1;
	if (line[i] == line[j])
		return (i + 1);
	while (line[i] && line[i] != line[j])
		i++;
	// i++;
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

int	pass_variable(char *line)
{
	int	i;

	i = 1;
	while (line[i] && line[i] != 39 && line[i] != 34
		&& line[i] != '<' && line[i] != '>' && line[i] != ' ')
		i++;
	return (i - 1);
}

int	is_variable_char(char c)
{
	if (c == ' ' || c == 34 || c == 39 || c == '|' || c == '$'
		|| c == '}' || c == '\0')
		return (1);
	return (0);
}

int	is_empty_brace(char *line, t_struct *minish)
{
	int		i;
	char	*tmp;
	char	*str;

	i = 2;
	while (is_variable_char(line[i]) == 0)
		i++;
	if (is_variable_char(line[i]) == 1)
	{
		printf("${%c}: bad substitution\n", line[i]);
		minish->parsing.error = 1;
		return (-1);
	}
	if (line[i] == '}' && line[i + 1] == ' ')
	{
		str = malloc(sizeof(char) * i - 1);
		if (str == NULL)
		{
			printf("error malloc\n");
			minish->parsing.error = 1;
			return (-1);
		}
		str[i - 2] = '\0';
		i--;
		while (i > 1)
		{
			str[i - 2] = line[i];
			i--;
		}
		tmp = get_variable(&minish->env.env_ms, str);
		free(str);
		if (tmp == NULL)
			return (0);
	}
	return (1);
}

int	is_empty_no_brace(char *line, t_struct *minish)
{
	int		i;
	int		j;
	char	*str;
	char	*tmp;

	i = 1;
	while (is_variable_char(line[i]) == 0)
		i++;
	str = malloc(sizeof(char) * i - 1);
	if (str == NULL)
	{
		printf("error malloc\n");
		minish->parsing.error = 1;
		return (-1);
	}
	j = i;
	str[i - 1] = '\0';
	i--;
	while (i > 0)
	{
		str[i - 1] = line[i];
		i--;
	}
	tmp = get_variable(&minish->env.env_ms, str);
	free(str);
	if (tmp == NULL && (line[j] == ' ' || line[j] == '\0'))
		return (0);
	return (1);
}

int	is_empty(char *line, t_struct *minish)
{
	int		i;

	i = 0;
	if (line[i] == '$' && (line[i + 1] == '\0' || line[i + 1] == ' '))
		return (1);
	if (line[i] == '$' && line[i + 1] == '{')
		return (is_empty_brace(line, minish));
	else if (line[i] == '$' && line[i] != '{')
		return (is_empty_no_brace(line, minish));
	return (1);
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
	else if (line[i] == '$')
	{
		j = is_empty(&line[i], minish);
		if (j != 0)
			minish->parsing.nb_arg++;
		while (line[i] && line[i] != ' ')
		{
			if (line[i] == 39 || line[i] == 34)
				i += pass_quotes(&line[i]);
			i++;
		}
		return (i);
	}
	minish->parsing.nb_arg++;
	while (line[i])
	{
		printf("test = [%s]\n", &line[i]);
		while (line[i] && line[i] != 39 && line[i] != 34
			&& line[i] != ' ' && line[i] != '$')
			i++;
		if (line[i] == 39 || line[i] == 34)
			i += pass_quotes(&line[i]);
		else if (line[i] == '$')
			i += pass_variable(&line[i]);
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
