/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:54:48 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/04 09:55:26 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_variable(char *prompt)
{
	int	i;
	int	ret;
	int	len;

	i = 0;
	ret = 0;
	len = 0;
	while (prompt[i] == ' ')
		i++;
	i += 6;
	while (prompt[i] == ' ')
		i++;
	while (prompt[i] != '=')
	{
		len++;
		i++;
	}
	i++;
	len++;
	if (prompt[i] == '"')
	{
		i++;
		ret = 1;
	}
	while ((ret == 1 && prompt[i] != '"') || (ret == 0 && prompt[i] != ' '))
	{
		i++;
		len++;
	}
	return (len);
}

