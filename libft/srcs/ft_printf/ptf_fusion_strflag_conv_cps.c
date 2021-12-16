/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_fusion_strflag_conv_cps.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 23:48:27 by ldermign          #+#    #+#             */
/*   Updated: 2021/09/18 16:40:19 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_cara_non_imp(int nbr, t_flag_len *flag)
{
	if (flag->minus == 1)
	{
		ft_putchar_ptf(nbr, flag);
		while (flag->nbr_width > 1 && flag->nbr_width--)
			ft_putchar_ptf(' ', flag);
	}
	else
	{
		while (flag->nbr_width > 1 && flag->nbr_width--)
			ft_putchar_ptf(' ', flag);
		ft_putchar_ptf(nbr, flag);
	}
}

void	fusion_c(int nbr, t_flag_len *flag)
{
	if (flag->nbr_width > 1)
	{
		flag->final_str_flag = ft_calloc(flag->nbr_width + 1, sizeof(char));
		if (flag->final_str_flag == NULL)
			return ;
	}
	if (flag->conv_per == 1 && flag->padded_zero == 1)
		ft_fill_with_c(flag->final_str_flag, '0', flag->nbr_width + 1);
	else
		ft_fill_with_c(flag->final_str_flag, ' ', flag->nbr_width + 1);
	if (nbr <= 31)
	{
		ft_cara_non_imp(nbr, flag);
		return ;
	}
	if (flag->minus == 1)
		flag->final_str_flag[0] = nbr;
	else
		flag->final_str_flag[flag->nbr_width - 1] = nbr;
}

void	fill_str_conv_p(char *str, int start, int len, t_flag_len *flag)
{
	int	i;
	int	max;

	i = 0;
	max = flag->nbr_width;
	if (flag->minus == 0)
	{
		while (str[i] && flag->final_str_flag[start] && start < max)
		{
			flag->final_str_flag[start] = str[i];
			i++;
			start++;
		}
	}
	else
	{
		while (i < len && str[i] && flag->final_str_flag[i])
		{
			flag->final_str_flag[i] = str[i];
			i++;
		}
	}
}

void	fusion_p(char *str, int max, int len, t_flag_len *flag)
{
	int	start;

	start = max - len;
	if (flag->nbr_width <= flag->nbr_precision)
	{
		start = 0;
		len = flag->nbr_precision;
	}
	flag->final_str_flag = ft_calloc(max + 1, sizeof(char));
	if (flag->final_str_flag == NULL)
		return ;
	ft_fill_with_c(flag->final_str_flag, ' ', max + 1);
	fill_str_conv_p(str, start, len, flag);
}

void	fusion_s(char *str, int start, int last, t_flag_len *flag)
{
	int	i;

	i = 0;
	if (flag->minus == 1)
	{
		start = 0;
		while (start < last && str[start] && flag->final_str_flag[start])
		{
			flag->final_str_flag[start] = str[start];
			start++;
		}
	}
	else
	{
		last = flag->size_final_str_flag;
		while (str[i] && flag->final_str_flag[start] && start <= last)
		{
			flag->final_str_flag[start] = str[i];
			i++;
			start++;
		}
	}
}
