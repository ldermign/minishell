/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_split_ms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:54:00 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/08 14:10:30 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_free(char **str)
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

static int	ft_len_word(const char *str, char c)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] && str[i] != c && str[i] != ' ')
	{
		i++;
		len++;
	}
	return (len);
}

static int	ft_word_count(const char *str)
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
		if (str[i] == ' ')
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

static char	**boucle(char **dst, char *str, int nbr_line)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = 0;
	while (str[i] && j < nbr_line)
	{
		size = ft_len_word(&str[i], ' ');
		dst[j] = (char *)malloc(sizeof(char) * size + 1);
		if (dst[j] == NULL)
			return (ft_free(dst));
		ft_strlcpy(dst[j], &str[i], size + 1);
		j++;
		i += size;
		while (str[i] && str[i] == ' ')
			i++;
	}
	dst[j] = NULL;
	return (dst);
}

char	**get_cmd_and_args_split(char *str)
{
	char	**dst;

	if (str == NULL)
		return (NULL);
	if (ft_word_count(str) == 0)
		return (NULL);
	dst = (char **)malloc(sizeof(char *) * (ft_word_count(str) + 1));
	if (dst == NULL)
		return (ft_free(dst));
	dst = boucle(dst, str, ft_word_count(str));
	return (dst);
}
