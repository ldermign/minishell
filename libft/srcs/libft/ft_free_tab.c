/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:20:17 by ldermign          #+#    #+#             */
/*   Updated: 2021/12/14 13:20:13 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(char **str_tab)
{
	int	i;

	i = 0;
	if (str_tab != NULL)
	{
		while (str_tab[i] != NULL)
		{
			free(str_tab[i]);
			i++;
		}
	}
	free(str_tab);
}
