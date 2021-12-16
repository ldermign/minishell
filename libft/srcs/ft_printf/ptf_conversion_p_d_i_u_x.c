/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_conversion_p_d_i_u_x.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 08:31:53 by ldermign          #+#    #+#             */
/*   Updated: 2021/09/18 16:40:19 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	particular_case(int arg_unsdint, int size, char *tmp, t_flag_len *flag)
{
	if ((arg_unsdint == 0 && flag->dot == 1 && flag->nbr_precision == 0
			&& flag->width == -1) || (flag->width == 1 && flag->precision == 1
			&& flag->nbr_width == 0 && flag->nbr_precision == 0
			&& arg_unsdint == 0))
	{
		free(tmp);
		return (1);
	}
	if (flag->width == 1 && flag->precision == 1 && (arg_unsdint == 0
			&& flag->nbr_width <= 1 && flag->nbr_precision == 0))
	{
		ft_putchar_ptf(' ', flag);
		free(tmp);
		return (1);
	}
	else if (size >= flag->nbr_precision && size >= flag->nbr_width)
	{
		ft_putstr_ptf(tmp, flag);
		free(tmp);
		return (1);
	}
	return (0);
}

void	conv_p(va_list ap, t_flag_len *flag)
{
	unsigned long	arg_unsdint;
	void			*adresse_ptr;
	char			*temp;
	char			*str_adresse;

	adresse_ptr = va_arg(ap, void *);
	arg_unsdint = (unsigned long)(adresse_ptr);
	str_adresse = ft_itoa_base(arg_unsdint, "0123456789abcdef");
	if (adresse_ptr == NULL && flag->precision == -1 && flag->dot == 1)
		temp = ft_strjoin("0x", "");
	else
		temp = ft_strjoin("0x", str_adresse);
	if (ft_no_flag(flag) || flag->nbr_width < (int)ft_strlen(temp))
		ft_putstr_ptf(temp, flag);
	else
	{
		fusion_conv_strflag(temp, ft_strlen(temp), flag);
		ft_putstr_ptf(flag->final_str_flag, flag);
	}
	free(temp);
	free(str_adresse);
}

void	conv_d_i(va_list ap, t_flag_len *flag)
{
	int		arg_int;
	int		size_temp;
	char	*temp;

	arg_int = va_arg(ap, int);
	temp = ft_itoa(arg_int);
	size_temp = ft_strlen(temp);
	if (flag->dot == 1 && arg_int == 0
		&& ((flag->precision == 1 && flag->nbr_width == 0
				&& flag->nbr_precision == 0)
			|| ((flag->nbr_width == 0 && flag->precision == -1)
				|| (flag->width == -1 && flag->nbr_precision == 0)
				|| (flag->nbr_width == 0 && flag->nbr_precision == 0))))
	{
		free(temp);
		return ;
	}
	if (size_temp > flag->nbr_precision && size_temp > flag->nbr_width)
		ft_putstr_ptf(temp, flag);
	else
	{
		fusion_conv_strflag(temp, arg_int, flag);
		ft_putstr_ptf(flag->final_str_flag, flag);
	}
	free(temp);
}

void	conv_u(va_list ap, t_flag_len *flag)
{
	unsigned int	arg_unsdint;
	int				size_temp;
	char			*temp;

	arg_unsdint = va_arg(ap, unsigned int);
	temp = ft_itoa_unsd(arg_unsdint);
	size_temp = ft_strlen(temp);
	if (particular_case(arg_unsdint, size_temp, temp, flag) == 1)
		return ;
	else
	{
		fusion_conv_strflag(temp, arg_unsdint, flag);
		ft_putstr_ptf(flag->final_str_flag, flag);
	}
	free(temp);
}

void	conv_x(char c, va_list ap, t_flag_len *flag)
{
	unsigned int	arg_unsdint;
	int				size_temp;
	char			*base;
	char			*temp;

	arg_unsdint = va_arg(ap, unsigned int);
	if (c == 'x')
		base = "0123456789abcdef";
	if (c == 'X')
		base = "0123456789ABCDEF";
	temp = ft_itoa_base(arg_unsdint, base);
	size_temp = ft_strlen(temp);
	if (particular_case(arg_unsdint, size_temp, temp, flag) == 1)
		return ;
	else
	{
		fusion_conv_strflag(temp, arg_unsdint, flag);
		ft_putstr_ptf(flag->final_str_flag, flag);
	}
	free(temp);
}
