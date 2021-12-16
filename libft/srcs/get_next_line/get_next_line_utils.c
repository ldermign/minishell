/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 11:22:50 by ldermign          #+#    #+#             */
/*   Updated: 2021/09/18 16:39:49 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_reader(char *reader)
{
	free(reader);
	return (1);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*dst;
	int		i;
	int		j;
	int		size_tot;

	if (s1 == NULL)
		s1 = ft_strdup("");
	if (s2 == NULL)
		return (0);
	i = -1;
	j = -1;
	size_tot = ft_strlen((const char *)s1) + ft_strlen((const char *)s2) + 1;
	dst = (char *)malloc(sizeof(char) * size_tot);
	if (dst == NULL)
		return (NULL);
	while (s1[++i])
		dst[i] = s1[i];
	free(s1);
	while (s2[++j])
	{
		dst[i] = s2[j];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup_gnl(char *str)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	dst = malloc(sizeof(char) * (i + 1));
	if (dst == NULL)
	{
		free(str);
		return (NULL);
	}
	while (str[j] && str[j] != '\n')
	{
		dst[j] = str[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}
