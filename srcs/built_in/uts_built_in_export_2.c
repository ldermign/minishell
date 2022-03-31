/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_built_in_export_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:54:48 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/31 14:28:36 by ldermign         ###   ########.fr       */
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

static int	light_parse_export_2(char *str, int i)
{
	if (str[i] != '=' && str[i] != '\0')
	{
		fprintf(stderr, "minishell: export: '%s': not a valid identifier\n",
			str);
		g_sig_error = 1;
		return (-1);
	}
	while (str[i] && str[i] != '&' && str[i] != '(' && str[i] != ')'
		&& str[i] != ';' && str[i] != '<' && str[i] != '>' && str[i] != '|')
		i++;
	if (str[i] != '\0')
	{
		fprintf(stderr, "bash: syntax error near unexpected token `%c'\n",
			str[i]);
		g_sig_error = 2;
		return (-1);
	}
	return (EXIT_SUCCESS);
}

int	light_parse_export(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (ft_is_digit(str[i]) || str[i] == '=')
	{
		fprintf(stderr, "minishell: export: '%s': not a valid identifier\n",
			str);
		g_sig_error = 1;
		return (-1);
	}
	while (str[i] && (ft_is_alpha(str[i]) || str[i] == '_'
			|| ft_is_digit(str[i])))
		i++;
	if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
	{
		ret = 1;
		i++;
	}
	if (light_parse_export_2(str, i) == -1)
		return (-1);
	return (ret);
}

static void	fill_new_str(t_it *it, char *prompt)
{
	while (it->j < it->len)
	{
		if (it->add == 1 && it->pos == -1 && prompt[it->i + 1]
			&& prompt[it->i] == '+' && prompt[it->i + 1] == '=')
			it->i++;
		it->str[it->j] = prompt[it->i];
		if (it->ret == 0 && prompt[it->i] == '=' && prompt[it->i + 1] == '"')
		{
			it->i++;
			it->ret = 1;
		}
		it->j++;
		it->i++;
	}
	it->str[it->j] = '\0';
}

char	*get_good_var(char *prompt, int size, int add, int pos)
{
	t_it	it;

	init_struct_it(&it);
	it.str = malloc(sizeof(char) * (size + 1));
	if (it.str == NULL)
	{
		fprintf(stderr, "Bad malloc.\n");
		return (NULL);
	}
	if (add == 1 && pos != -1)
	{
		while (prompt[it.i] && prompt[it.i] != '=')
			it.i++;
		it.i++;
	}
	it.pos = pos;
	it.add = add;
	it.len = size;
	fill_new_str(&it, prompt);
	return (it.str);
}
