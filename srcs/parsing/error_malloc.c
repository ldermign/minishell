/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 00:48:54 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/05 00:49:35 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*error_malloc_null(t_struct *minish)
{
	printf("error malloc\n");
	minish->parsing.error = 1;
	return (NULL);
}

int	error_malloc(t_struct *minish)
{
	printf("error malloc\n");
	minish->parsing.error = 1;
	return (-1);
}
