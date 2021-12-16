/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_init_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:46:59 by ldermign          #+#    #+#             */
/*   Updated: 2021/09/18 16:40:19 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_init_struct_flag(t_flag_len *flag)
{
	flag->minus = 0;
	flag->padded_zero = 0;
	flag->width = -1;
	flag->precision = -1;
	flag->nbr_width = 0;
	flag->nbr_precision = 0;
	flag->final_str_flag = NULL;
	flag->size_final_str_flag = 0;
	flag->conv_c = 0;
	flag->conv_s = 0;
	flag->conv_p = 0;
	flag->conv_d_i = 0;
	flag->conv_u = 0;
	flag->conv_x = 0;
	flag->conv_per = 0;
	flag->dot = 0;
	flag->tmp_size = 0;
}

int	ft_nblen(long n)
{
	int	len_int;

	len_int = 1;
	if (n < 0)
	{
		n = -n;
		len_int++;
	}
	while (n >= 10)
	{
		n /= 10;
		len_int++;
	}
	return (len_int);
}

void	string_of_flag_to_int(char *str, va_list ap, t_flag_len *flag)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '*')
	{
		flag->nbr_width = va_arg(ap, int);
		i++;
	}
	else if (str[i] && ft_is_digit(str[i]))
	{
		flag->nbr_width = ft_atoi_printf(&str[i]);
		i += ft_nblen(flag->nbr_width) + 1;
	}
	if (str[i] && str[i] == '.')
		i++;
	if (str[i] && str[i] == '*')
	{
		flag->nbr_precision = va_arg(ap, int);
		i++;
	}
	else
		flag->nbr_precision = ft_atoi_printf(&str[i]);
}

void	check_flag_padded_minus(char *str, t_flag_len *flag)
{
	if (*str == '0')
	{
		flag->padded_zero = 1;
		str++;
	}
	if (*str == '-')
		flag->minus = 1;
}

int	check_flags(const char *str, va_list ap, t_flag_len *flag)
{
	int	i;

	i = 0;
	ft_init_struct_flag(flag);
	check_flag_padded_minus((char *)str, flag);
	if (str[i] == '0' || str[i] == '-')
		while (str[i] == '0' || str[i] == '-')
			i++;
	string_of_flag_to_int((char *)&str[i], ap, flag);
	if (str[i] && str[i + 1] && (str[i] == '*' || ft_is_digit(str[i])) && ++i)
	{
		flag->width = 1;
		while (str[i] && ft_is_digit(str[i]))
			i++;
	}
	if (str[i] == '.')
		flag->dot = 1;
	if (str[i] == '.' && ++i && (ft_is_digit(str[i]) || str[i] == '*'))
	{
		flag->precision = 1;
		if (str[i] && (str[i] == '*' || ft_is_digit(str[i])) && ++i)
			while (str[i] && ft_is_digit(str[i]))
				i++;
	}
	return (i);
}
