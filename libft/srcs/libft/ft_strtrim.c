/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:54:59 by ldermign          #+#    #+#             */
/*   Updated: 2021/04/25 14:04:47 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charset(char const *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int	ft_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && ft_charset(set, s1[i]))
		i++;
	return (i);
}

int	ft_end(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen((char *)s1);
	while (i > 0 && ft_charset(set, s1[i - 1]))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		len;
	char	*dst;

	if (!s1 || !set)
		return (NULL);
	start = ft_start(s1, set);
	len = ft_end(&s1[start], set) + 1;
	dst = (char *)malloc(sizeof(char) * len);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, (char *)&s1[start], len);
	return (dst);
}
