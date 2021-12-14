/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:41:19 by ldermign          #+#    #+#             */
/*   Updated: 2021/09/18 16:43:16 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
**	Structures cspdiuxX%
*/

typedef struct s_struct
{
	int		final_len;
	int		minus;
	int		padded_zero;
	int		width;
	int		precision;
	int		nbr_width;
	int		nbr_precision;
	char	*str_width;
	char	*final_str_flag;
	size_t	size_final_str_flag;
	int		conv_c;
	int		conv_s;
	int		conv_p;
	int		conv_d_i;
	int		conv_u;
	int		conv_x;
	int		conv_per;
	int		dot;
	int		tmp_size;
}				t_flag_len;

/*
**	Checks
*/

int				ft_check_flag(const char *str);
int				ft_is_digit(char c);
int				ft_is_conv(char c);
int				ft_no_flag(t_flag_len *flag);
int				ft_is_alpha(char c);

/*
**	Utils
*/

void			ft_putchar_ptf(char c, t_flag_len *len);
void			ft_putstr_ptf(char *str, t_flag_len *len);
char			*ft_itoa(int nb);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_atoi_printf(char *str);
void			*fill_from_end(char *dst, char *src, size_t n);
void			ft_fill_with_c(char *str, char c, int size);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_itoa_base(size_t nbr, char *base);
char			*ft_itoa_unsd(unsigned int n);
int				which_is_smaller(int width, int prec, int len_str);

/*
**	Flags
*/

void			ft_init_flag_len_flag(t_flag_len *flag);
void			string_of_flag_to_int(char *str, va_list ap, t_flag_len *flag);
int				check_flags(const char *str, va_list ap, t_flag_len *flag);
void			flag_precision(t_flag_len *flag);
void			flag_width(t_flag_len *flag);

/*
**	Conversion
*/

void			conv_u(va_list ap, t_flag_len *flag);
void			conv_x(char c, va_list ap, t_flag_len *len);
void			conv_p(va_list ap, t_flag_len *flag);
void			conv_d_i(va_list ap, t_flag_len *flag);
void			conv_s(va_list ap, t_flag_len *flag);
void			conv_c(va_list ap, t_flag_len *flag);
void			conv_per(t_flag_len *flag);
void			fusion_conv_strflag(char *str, int nbr, t_flag_len *flag);
int				ft_printf(const char *str, ...);

/*
**	Utils fusion
*/

int				alloc_size1(int width, int prec, int len_str, t_flag_len *flag);
void			ft_final_size(int width, int prec, int len_str,
					t_flag_len *flag);
int				where_to_begin(int prec, int ret, int len, t_flag_len *flag);
int				where_last(char *str, int prec, int ret, t_flag_len *flag);

/*
**	Fusion str flags and str conv
*/

void			join_width_and_precision(t_flag_len *flag);
void			fusion_s(char *str, int start, int last, t_flag_len *flag);
void			prep_fus(char *str, int width, int prec, t_flag_len *flag);
void			fusion_d_i_u_x(char *str, int nbr, t_flag_len *flag);
void			fusion_p(char *str, int max, int len, t_flag_len *flag);
void			fusion_c(int nbr, t_flag_len *flag);
void			fusion_c(int nbr, t_flag_len *flag);

#endif
