/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_utils_itoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:57:56 by ldermign          #+#    #+#             */
/*   Updated: 2021/09/18 16:40:19 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_len_nbr(size_t nbr, size_t size_base)
{
	size_t	size_nbr;

	size_nbr = 0;
	if (nbr == 0)
		size_nbr = 1;
	if (nbr < 0)
	{
		nbr *= -1;
		size_nbr++;
	}
	while (nbr > 0)
	{
		nbr /= size_base;
		size_nbr++;
	}
	return (size_nbr);
}

char	*ft_itoa_base(size_t nbr, char *base)
{
	size_t	size_nbr;
	size_t	temp;
	char	*dst;

	size_nbr = ft_len_nbr(nbr, ft_strlen(base));
	dst = malloc(sizeof(char) * (size_nbr + 1));
	if (dst == NULL)
		return (NULL);
	dst[size_nbr--] = '\0';
	if (nbr == 0)
		dst[0] = '0';
	else if (nbr < 0)
	{
		dst[0] = '-';
		nbr *= -1;
	}
	while (nbr > 0)
	{
		temp = nbr % ft_strlen(base);
		dst[size_nbr] = base[temp];
		nbr /= ft_strlen(base);
		size_nbr--;
	}
	return (dst);
}

static int	ft_len(long n)
{
	int	len_int;

	len_int = 0;
	if (n < 0)
		n = -n;
	while (n >= 10)
	{
		n /= 10;
		len_int++;
	}
	return (len_int + 1);
}

char	*ft_itoa_unsd(unsigned int n)
{
	char			*dst;
	int				len;
	unsigned int	nb;

	nb = n;
	len = ft_len(nb) + (nb < 0);
	dst = (char *)malloc(sizeof(char) * len + 1 + (n < 0));
	if (dst == NULL)
		return (NULL);
	if (nb < 0)
	{
		*dst = '-';
		nb = -nb;
	}
	dst[len--] = '\0';
	while (len >= (n < 0))
	{
		dst[len--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (dst);
}
