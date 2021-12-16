/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_alloc_right_size.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:18:22 by ldermign          #+#    #+#             */
/*   Updated: 2021/09/18 16:40:19 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	alloc_if_w_and_p2(int width, int prec, int len_str, t_flag_len *flag)
{
	if (width >= len_str)
	{
		flag->final_str_flag = ft_calloc(width + 1, sizeof(char));
		if (flag->final_str_flag == NULL)
			return (0);
	}
	else if (prec >= len_str)
	{
		flag->final_str_flag = ft_calloc(len_str + 1, sizeof(char));
		if (flag->final_str_flag == NULL)
			return (0);
	}
	else if (prec < len_str)
	{
		flag->final_str_flag = ft_calloc(prec + 1, sizeof(char));
		if (flag->final_str_flag == NULL)
			return (0);
	}
	return (1);
}

int	alloc_if_w_and_p1(int width, int prec, int len_str, t_flag_len *flag)
{
	if (width >= prec || prec == 0)
	{
		flag->final_str_flag = ft_calloc(width + 1, sizeof(char));
		if (flag->final_str_flag == NULL)
			return (0);
	}
	else if (prec > width)
	{
		if (alloc_if_w_and_p2(width, prec, len_str, flag) == 0)
			return (0);
	}
	return (1);
}

int	alloc_size2(int width, int prec, int len_str, t_flag_len *flag)
{
	if (flag->precision == 1 && flag->width == 1)
	{
		if (alloc_if_w_and_p1(width, prec, len_str, flag) == 0)
			return (0);
	}
	else if ((len_str <= width && flag->precision == -1)
		|| (flag->dot == 1 && prec == 0 && width > 0))
	{
		flag->final_str_flag = ft_calloc(width + 1, sizeof(char));
		if (flag->final_str_flag == NULL)
			return (0);
	}
	return (1);
}

int	alloc_size1(int width, int prec, int len_str, t_flag_len *flag)
{
	if (alloc_size2(width, prec, len_str, flag) == 0)
		return (0);
	else if ((len_str >= width && flag->precision == -1)
		|| (len_str <= prec && flag->width == -1))
	{
		flag->final_str_flag = ft_calloc(len_str + 1, sizeof(char));
		if (flag->final_str_flag == NULL)
			return (0);
	}
	else if ((len_str >= prec && flag->width == -1))
	{
		flag->final_str_flag = ft_calloc(prec + 1, sizeof(char));
		if (flag->final_str_flag == NULL)
			return (0);
	}
	return (1);
}
