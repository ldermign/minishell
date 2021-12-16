/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_fusion_strflag_conv_s_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:00:28 by ldermign          #+#    #+#             */
/*   Updated: 2021/09/18 16:40:19 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_final_size(int width, int prec, int len_str, t_flag_len *flag)
{
	if ((len_str <= width && flag->precision == -1)
		|| (flag->dot == 1 && prec == 0 && width > 0))
		flag->size_final_str_flag = width;
	else if ((len_str >= width && flag->precision == -1)
		|| (len_str <= prec && flag->width == -1))
		flag->size_final_str_flag = len_str;
	else if (len_str > prec && flag->width == -1)
		flag->size_final_str_flag = prec;
	if (flag->precision == 1 && flag->width == 1)
	{
		if (width >= prec)
			flag->size_final_str_flag = width;
		if (prec > width)
		{
			if (width >= len_str)
				flag->size_final_str_flag = width;
			else if (prec >= len_str)
				flag->size_final_str_flag = len_str;
			else if (prec < len_str)
				flag->size_final_str_flag = prec;
		}
	}
}

int	where_to_begin(int prec, int ret, int len, t_flag_len *flag)
{
	int	w_minus_len;
	int	width;
	int	start;
	int	min;

	width = flag->nbr_width;
	w_minus_len = width - len;
	start = 0;
	min = which_is_smaller(width, prec, len);
	if ((flag->width == 1 && flag->precision == -1)
		|| (width > len && flag->precision == -1))
		start = flag->size_final_str_flag - min;
	else if (flag->minus == 0 && len == (int)flag->size_final_str_flag
		&& ret < 0)
		start = 0;
	else if (flag->width == 1 && flag->precision == 1)
	{
		if (ret < 0 && w_minus_len == 1)
			start = 1;
		else if (ret < 0 && w_minus_len == len)
			start = len;
		else if ((ret > 0 && prec >= width && width >= len) || width >= prec)
			start = flag->size_final_str_flag - min;
	}
	return (start);
}

int	where_last(char *str, int prec, int ret, t_flag_len *flag)
{
	int	len_str;
	int	width;
	int	last;

	len_str = ft_strlen(str);
	width = flag->nbr_width;
	if ((len_str >= prec && prec >= width) || flag->precision == -1
		|| (prec >= len_str && len_str >= width))
		last = flag->size_final_str_flag;
	else if (len_str >= prec && width >= prec)
		last = prec;
	else
		last = which_is_smaller(width, prec, len_str);
	if (ret < 0)
		last = len_str;
	return (last);
}
