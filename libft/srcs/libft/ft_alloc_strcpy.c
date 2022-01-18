/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_strcpy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 18:26:44 by ldermign          #+#    #+#             */
/*   Updated: 2022/01/16 18:46:29 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_alloc_strcpy(char *str)
{
	int		i;
	int		len;
	char	*dst;

	if (str == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(str) + 1;
	dst = malloc(sizeof(char) * len + 1);
	if (dst == NULL)
		return (NULL);
	while (str[i] && i < len)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
