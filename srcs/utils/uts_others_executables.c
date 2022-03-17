/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_others_executables.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 09:45:28 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/17 09:50:01 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell"

int	is_new_executable(char *str)
{
	int	i;

	i = 0;
	if (str[0] && str[0] == '.')
	{
		if (str[1] && str[1] == '/')
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

char	*new_path(char *to_copy)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = 0;
	while (to_copy[i] && to_copy[i] == ' ')
		i++
	j = i;
	len = 0;
	while (to_copy[i] && to_copy[i] != ' ')
	{
		i++;
		len++;
	}
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (str[j])
	{
		new[i] = str[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}