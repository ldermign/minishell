/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 00:48:54 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/29 10:01:15 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*error_malloc_null(t_struct *minish)
{
	fprintf(stderr, "error malloc\n");
	minish->parsing.error = 1;
	return (NULL);
}

int	error_malloc(t_struct *minish)
{
	fprintf(stderr, "error malloc\n");
	minish->parsing.error = 1;
	return (-1);
}
