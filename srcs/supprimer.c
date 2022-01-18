/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supprimer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 20:17:21 by ldermign          #+#    #+#             */
/*   Updated: 2022/01/14 20:22:26 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tab_char(char **tabl)
{
	int	i;

	i = 0;
	printf(GREEN"--------------------\n");
	while (tabl[i])
	{
		printf("Line %d = [%s]\n", i, tabl[i]);
		i++;
	}
	printf("--------------------\n"NORMAL);
}