/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 11:14:02 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/18 13:48:25 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig_error(char *str, int nbr)
{
	static int	new_error = 0;

	if (nbr == -1)
		return (new_error);
	// fprintf(stderr, "OUI ? new = %d, nbr = %d\n", new_error, nbr);
	new_error = nbr;
	if (str != NULL)
		perror(str);
	// fprintf(stderr, "nbr = [%d], new_error (b4) = [%d], str = [%s]\n", nbr, new_error, str);
	return (new_error);
}