/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 15:31:27 by ldermign          #+#    #+#             */
/*   Updated: 2021/06/15 08:15:58 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free(char **str)
{
	int	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

int	ft_len_word(const char *str, char c)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] && str[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

int	ft_word_count(const char *str, char c)
{
	int	i;
	int	word_count;
	int	count_switch;

	i = 0;
	word_count = 0;
	count_switch = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			count_switch = 0;
		else if (count_switch == 0)
		{
			count_switch = 1;
			word_count++;
		}
		i++;
	}
	return (word_count);
}

char	**boucle(char **dst, char const *str, char c)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = 0;
	while (str[i] && j < ft_word_count(str, c))
	{
		while (str[i] && str[i] == c)
			i++;
		size = ft_len_word(&str[i], c);
		dst[j] = (char *)malloc(sizeof(char) * size + 1);
		if (dst[j] == NULL)
			return (ft_free(dst));
		ft_strlcpy(dst[j], &str[i], size + 1);
		j++;
		i += size;
	}
	dst[j] = NULL;
	return (dst);
}

char	**ft_split(char const *str, char c)
{
	char	**dests;

	if (str == NULL)
		return (NULL);
	dests = (char **)malloc(sizeof(char *) * (ft_word_count(str, c) + 1));
	if (dests == NULL)
		return (ft_free(dests));
	dests = boucle(dests, str, c);
	return (dests);
}
