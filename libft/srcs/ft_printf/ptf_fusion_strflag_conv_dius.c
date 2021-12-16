/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_fusion_strflag_conv_dius.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 09:53:45 by ldermign          #+#    #+#             */
/*   Updated: 2021/09/18 16:40:19 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbr_inf_zero(int space, int zero, int size, t_flag_len *flag)
{
	if (flag->nbr_width <= flag->nbr_precision)
	{
		ft_putchar_ptf('-', flag);
		return (1);
	}
	else if (flag->padded_zero == 1 && flag->precision == -1)
	{
		flag->final_str_flag[0] = '-';
		return (1);
	}
	else if (flag->nbr_precision < flag->nbr_width)
	{
		if (flag->minus == 1 && flag->width == 1)
		{
			flag->final_str_flag[0] = '-';
			if (zero < (int)flag->size_final_str_flag && size < zero)
				flag->final_str_flag[--zero] = '0';
		}
		else if (flag->minus == 0)
			if (flag->conv_x == 0 && flag->conv_u == 0)
				flag->final_str_flag[--space] = '-';
		return (1);
	}
	return (0);
}

size_t	check_where_zero_or_space(t_flag_len *flag, char c)
{
	size_t	last_seen;
	size_t	size;
	int		i;

	i = 0;
	last_seen = 0;
	size = flag->size_final_str_flag;
	if ((flag->final_str_flag[size - 1] == c
			&& (flag->final_str_flag[0] == c || flag->final_str_flag[0] != c))
		|| (flag->final_str_flag[size - 1] != c
			&& flag->final_str_flag[0] != c))
		return (size);
	while (flag->final_str_flag[last_seen] == c)
		last_seen++;
	return (last_seen);
}

int	fill_conv_d_str(char *str, int size_nbr, int zero, t_flag_len *flag)
{
	while (size_nbr >= 0 && zero >= 0)
	{
		if ((str[size_nbr] != '\0' && ft_is_digit(str[size_nbr]))
			|| ft_is_alpha(str[size_nbr]))
			flag->final_str_flag[zero] = str[size_nbr];
		if (str[size_nbr] == '-' && flag->final_str_flag[zero] == ' ')
			flag->final_str_flag[zero] = str[size_nbr];
		size_nbr--;
		zero--;
	}
	return (1);
}

void	fusion_d_i_u_x(char *str, int nbr, t_flag_len *flag)
{
	int	ret;
	int	i;
	int	size_nbr;
	int	place_zero;
	int	place_space;

	i = 0;
	ret = 0;
	size_nbr = ft_strlen(str);
	join_width_and_precision(flag);
	place_zero = check_where_zero_or_space(flag, '0');
	place_space = check_where_zero_or_space(flag, ' ');
	if (nbr == 0 && flag->dot == 1 && flag->nbr_precision == 0)
		str[0] = ' ';
	if (nbr < 0)
		ft_nbr_inf_zero(place_space, place_zero, size_nbr, flag);
	if (nbr < 0 && flag->minus == 1 && flag->nbr_precision < flag->nbr_width)
		place_zero++;
	if (flag->minus == 1 && ((size_nbr && flag->precision == -1)
			|| (flag->nbr_precision < size_nbr && flag->precision == 1)))
		place_zero = size_nbr;
	ret = fill_conv_d_str(str, size_nbr, place_zero, flag);
	if (ret == 0 && flag->nbr_width > flag->nbr_precision
		&& flag->padded_zero == 1 && size_nbr == 3)
		flag->final_str_flag[0] = '-';
}

void	prep_fus(char *str, int width, int prec, t_flag_len *flag)
{
	int	len_str;
	int	start;
	int	last;
	int	ret;

	len_str = ft_strlen(str);
	ret = prec;
	if (ret < 0)
		prec *= -1;
	if (alloc_size1(width, prec, len_str, flag) == 0)
		return ;
	ft_final_size(width, prec, len_str, flag);
	ft_fill_with_c(flag->final_str_flag, ' ', flag->size_final_str_flag + 1);
	if ((flag->precision == 1 && flag->nbr_precision == 0)
		|| (flag->dot == 1 && prec == 0 && width > 0))
		return ;
	start = where_to_begin(prec, ret, len_str, flag);
	last = where_last(str, prec, ret, flag);
	fusion_s(str, start, last, flag);
}
