/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_join_width_preci.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 09:36:41 by ldermign          #+#    #+#             */
/*   Updated: 2021/09/18 16:40:19 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	flip_zero_and_space(int here, int size, t_flag_len *flag)
{
	int		i;
	char	swap;

	i = 0;
	if (size > here && here > 0)
	{
		size--;
		if (here == size)
			here--;
		if (flag->final_str_flag[0] == '-')
			i++;
		if (flag->final_str_flag[size] == '\0')
			size--;
		while (size > here && flag->final_str_flag[size] != '\0')
		{
			swap = flag->final_str_flag[size];
			flag->final_str_flag[size] = flag->final_str_flag[i];
			flag->final_str_flag[i] = swap;
			size--;
			i++;
		}
	}
}

void	flip_zero_and_space_init(t_flag_len *flag)
{
	size_t	here;
	size_t	size;

	size = flag->size_final_str_flag;
	here = 0;
	while (flag->final_str_flag[here + 1] && (here < flag->size_final_str_flag))
	{
		here++;
		if (flag->final_str_flag[here] != flag->final_str_flag[here + 1])
			break ;
	}
	flip_zero_and_space(here, size, flag);
}

void	width_sup(t_flag_len *flag)
{
	int	length;
	int	max;
	int	ret;

	length = flag->nbr_width;
	max = flag->nbr_precision;
	ret = length;
	while (max >= 0)
	{
		flag->final_str_flag[length] = '0';
		max--;
		length--;
	}
	while (length >= 0)
	{
		flag->final_str_flag[length] = ' ';
		length--;
	}
	flag->final_str_flag[ret] = '\0';
}

int	size_final_str(t_flag_len *flag)
{
	if (flag->nbr_precision >= flag->nbr_width)
		return (flag->nbr_precision);
	else
		return (flag->nbr_width);
}

void	join_width_and_precision(t_flag_len *flag)
{
	flag->tmp_size = 0;
	if (flag->width == 1 || flag->precision == 1)
	{
		flag->tmp_size = size_final_str(flag);
		flag->final_str_flag = malloc(sizeof(char) * (flag->tmp_size + 1));
		if (flag->final_str_flag == NULL)
			return ;
	}
	if (flag->width == 1 && flag->precision == 1)
	{
		if (flag->nbr_precision >= flag->nbr_width)
			ft_fill_with_c(flag->final_str_flag, '0', flag->tmp_size + 1);
		else
			width_sup(flag);
	}
	if ((flag->width == 1 && flag->precision == -1 && flag->padded_zero == 0))
		ft_fill_with_c(flag->final_str_flag, ' ', flag->tmp_size + 1);
	else if ((flag->precision == 1 && flag->width == -1)
		|| (flag->padded_zero == 1 && flag->precision == -1)
		|| (flag->padded_zero == 1 && flag->nbr_precision < 0))
		ft_fill_with_c(flag->final_str_flag, '0', flag->tmp_size + 1);
	flag->size_final_str_flag = ft_strlen(flag->final_str_flag);
	if (flag->minus == 1)
		flip_zero_and_space_init(flag);
}
