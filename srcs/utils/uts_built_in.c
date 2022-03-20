/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:54:48 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/20 15:28:23 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_variable(char *prompt, int add, int pos)
{
	int	i;
	int	ret;
	int	len;

	i = 0;
	ret = 0;
	len = 0;
	if (add == 1 && pos != -1)
	{
		while (prompt[i] && prompt[i] != '=')
			i++;
		i++;
	}
	while (prompt[i])
	{
		i++;
		len++;
	}
	if (add == 1 && pos == -1)
		len--;
	return (len);
}

int	light_parse_export(char *prompt)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (prompt[i] && prompt[i] == ' ')
		i++;
	if (ft_is_digit(prompt[i]))
	{
		printf("minishell: export: '%s': not a valid identifier\n", prompt);
		return (-1);
	}
	while (prompt[i] && (ft_is_alpha(prompt[i])
			|| prompt[i] == '_' || ft_is_digit(prompt[i])))
		i++;
	if (prompt[i] == '+' && prompt[i + 1] && prompt[i + 1] == '=')
	{
		ret = 1;
		i++;
	}
	if (prompt[i] != '=' && prompt[i] != '\0')
	{
		printf("minishell: export: '%s': not a valid identifier\n", prompt);
		return (-1);
	}
	while (prompt[i] && prompt[i] != '&' && prompt[i] != '(' && prompt[i] != ')'
		&& prompt[i] != ';' && prompt[i] != '<' && prompt[i] != '>'
		&& prompt[i] != '|') // pas vraiment, checker commant il fonctionnne
		i++;
	if (prompt[i] != '\0')
	{
		printf("bash: syntax error near unexpected token `%c'\n", prompt[i]);
		return (-1);
	}
	return (ret);
}

int	light_parse_echo(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	i += 4;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] && str[i] == ' ')
		{
			while (str[i] && str[i] == ' ')
				i++;
			return (i);
		}
	}
	return (-1);
}

char	*get_good_variable(char *prompt, int size, int add, int pos)
{
	int		i;
	int		j;
	int		ret;
	char	*str;

	i = 0;
	ret = 0;
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
	{
		printf("Bad malloc.\n");
		return (NULL);
	}
	if (add == 1 && pos != -1)
	{
		while (prompt[i] && prompt[i] != '=')
			i++;
		i++;
	}
	j = 0;
	while (j < size)
	{
		if (add == 1 && pos == -1
			&& prompt[i + 1] && prompt[i] == '+' && prompt[i + 1] == '=')
			i++;
		str[j] = prompt[i];
		if (ret == 0 && prompt[i] == '=' && prompt[i + 1] == '"')
		{
			i++;
			ret = 1;
		}
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}
