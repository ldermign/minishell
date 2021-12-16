/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_conversion_s_c_per.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:37:39 by ldermign          #+#    #+#             */
/*   Updated: 2021/09/18 16:40:19 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	conv_s(va_list ap, t_flag_len *flag)
{
	char	*arg_char;
	int		size_arg;
	int		temp;

	arg_char = va_arg(ap, char *);
	size_arg = (int)ft_strlen(arg_char);
	if (arg_char != NULL && size_arg == 1)
		temp = ft_atoi_printf(arg_char);
	if (arg_char == NULL || arg_char == 0)
		arg_char = "(null)";
	if (flag->nbr_width == 0 && flag->nbr_precision == 0 && flag->dot == 1)
		return ;
	else if (ft_no_flag(flag) || flag->padded_zero == 1
		|| (flag->nbr_precision < 0 && flag->width == -1)
		|| (flag->nbr_precision < 0
			&& temp != 0 && size_arg > flag->nbr_width))
		ft_putstr_ptf(arg_char, flag);
	else
	{
		fusion_conv_strflag(arg_char, 0, flag);
		ft_putstr_ptf(flag->final_str_flag, flag);
	}
}

void	conv_c(va_list ap, t_flag_len *flag)
{
	int	cara;

	cara = va_arg(ap, int);
	if (flag->nbr_width <= 1)
		ft_putchar_ptf(cara, flag);
	else
	{
		fusion_conv_strflag(NULL, cara, flag);
		if (cara > 31)
			ft_putstr_ptf(flag->final_str_flag, flag);
	}
}

void	conv_per(t_flag_len *flag)
{
	const int	charac = '%';

	if ((1 >= flag->nbr_precision) && (1 >= flag->nbr_width))
		ft_putstr_ptf("%", flag);
	else
	{
		fusion_conv_strflag(NULL, charac, flag);
		ft_putstr_ptf(flag->final_str_flag, flag);
	}
}
