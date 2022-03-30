/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_built_in_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:51:52 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/30 14:20:52 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_export(char *new)
{
	new[0] = 'e';
	new[1] = 'x';
	new[2] = 'p';
	new[3] = 'o';
	new[4] = 'r';
	new[5] = 't';
	new[6] = ' ';
}

static void	copy_str_in_new(char *str, char *new, int i, int j)
{
	if (str[j])
	{
		new[i] = str[j];
		i++;
		j++;
		new[i] = '"';
		i++;
		while (str[j])
		{
			new[i] = str[j];
			i++;
			j++;
		}
		new[i] = '"';
		i++;
	}
	new[i] = '\n';
	i++;
	new[i] = '\0';
}

char	*get_str_export(char *str)
{
	t_it	it;
	int		len_tot;
	int		len_name;

	init_struct_it(&it);
	len_tot = ft_strlen(str) + 10;
	if (ft_int_strchr(str, '=') == 0)
		len_tot -= 2;
	len_name = 0;
	while (str[len_name] && str[len_name] != '=')
			len_name++;
	it.tmp1 = malloc(sizeof(char) * (len_tot + 1));
	if (it.tmp1 == NULL)
		return (NULL);
	get_export(it.tmp1);
	it.i = 7;
	len_name += 7;
	while (it.i < len_name)
	{
		it.tmp1[it.i] = str[it.j];
		it.i++;
		it.j++;
	}
	copy_str_in_new(str, it.tmp1, it.i, it.j);
	return (it.tmp1);
}
