/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 12:23:12 by ldermign          #+#    #+#             */
/*   Updated: 2021/09/18 16:39:53 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_return_in_str(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '\n')
				return (1);
			i++;
		}
	}
	return (0);
}

char	*ft_last_call(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str == NULL)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	new = malloc(sizeof(char) * ((ft_strlen(str) - i) + 1));
	if (new == NULL)
		return (NULL);
	i++;
	while (str[i])
		new[j++] = str[i++];
	new[j] = '\0';
	free(str);
	return (new);
}

int	get_next_line(int fd, char **line)
{
	int			place_in_fd;
	char		*reader;
	static char	*dst;

	place_in_fd = 1;
	reader = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (reader == NULL)
		return (-1);
	if ((fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		&& (ft_free_reader(reader) == 1))
		return (-1);
	while (!ft_return_in_str(dst) && place_in_fd != 0)
	{
		place_in_fd = read(fd, reader, BUFFER_SIZE);
		if ((place_in_fd == -1) && (ft_free_reader(reader) == 1))
			return (-1);
		reader[place_in_fd] = '\0';
		dst = ft_strjoin_gnl(dst, reader);
	}
	free(reader);
	*line = ft_strdup_gnl(dst);
	dst = ft_last_call(dst);
	if (place_in_fd == 0 && dst == NULL)
		return (0);
	return (1);
}
