# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/12 19:45:34 by ldermign          #+#    #+#              #
#    Updated: 2022/01/16 23:47:29 by ldermign         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRCS	=	./srcs/libft/ft_alloc_strcat.c \
			./srcs/libft/ft_alloc_strcpy.c \
			./srcs/libft/ft_atoi.c \
			./srcs/libft/ft_atol.c \
			./srcs/libft/ft_binary.c \
			./srcs/libft/ft_bzero.c \
			./srcs/libft/ft_calloc.c \
			./srcs/libft/ft_free_tab.c \
			./srcs/libft/ft_int_strchr.c \
			./srcs/libft/ft_isalnum.c \
			./srcs/libft/ft_isalpha.c \
			./srcs/libft/ft_isascii.c \
			./srcs/libft/ft_isdigit.c \
			./srcs/libft/ft_isprint.c \
			./srcs/libft/ft_itoa.c \
			./srcs/libft/ft_len_int.c \
			./srcs/libft/ft_lstadd_back.c \
			./srcs/libft/ft_lstadd_front.c \
			./srcs/libft/ft_lstdel_all.c \
			./srcs/libft/ft_lstdelone.c \
			./srcs/libft/ft_lstnew.c \
			./srcs/libft/ft_lstsize.c \
			./srcs/libft/ft_memccpy.c \
			./srcs/libft/ft_memchr.c \
			./srcs/libft/ft_memcmp.c \
			./srcs/libft/ft_memcpy.c \
			./srcs/libft/ft_memmove.c \
			./srcs/libft/ft_memset.c \
			./srcs/libft/ft_pos_strchr.c \
			./srcs/libft/ft_pos_strstr.c \
			./srcs/libft/ft_putchar.c \
			./srcs/libft/ft_putchar_fd.c \
			./srcs/libft/ft_putendl_fd.c \
			./srcs/libft/ft_putnbr.c \
			./srcs/libft/ft_putnbr_fd.c \
			./srcs/libft/ft_putstr.c \
			./srcs/libft/ft_putstr_fd.c \
			./srcs/libft/ft_random.c \
			./srcs/libft/ft_split.c \
			./srcs/libft/ft_strcat.c \
			./srcs/libft/ft_strchr.c \
			./srcs/libft/ft_strcmp.c \
			./srcs/libft/ft_strcpy.c \
			./srcs/libft/ft_strdup.c \
			./srcs/libft/ft_strjoin.c \
			./srcs/libft/ft_strlcat.c \
			./srcs/libft/ft_strlcpy.c \
			./srcs/libft/ft_strlen.c \
			./srcs/libft/ft_strmapi.c \
			./srcs/libft/ft_strncat.c \
			./srcs/libft/ft_strncmp.c \
			./srcs/libft/ft_strncpy.c \
			./srcs/libft/ft_strnstr.c \
			./srcs/libft/ft_strrchr.c \
			./srcs/libft/ft_strtrim.c \
			./srcs/libft/ft_substr.c \
			./srcs/libft/ft_swap.c \
			./srcs/libft/ft_tolower.c \
			./srcs/libft/ft_toupper.c

# Gnl srcs
SRCS	+=	./srcs/get_next_line/get_next_line.c \
			./srcs/get_next_line/get_next_line_utils.c

# Printf srcs
SRCS	+=	./srcs/ft_printf/ft_printf.c \
			./srcs/ft_printf/ptf_alloc_right_size.c \
            ./srcs/ft_printf/ptf_check.c \
            ./srcs/ft_printf/ptf_conversion_p_d_i_u_x.c \
            ./srcs/ft_printf/ptf_conversion_s_c_per.c \
            ./srcs/ft_printf/ptf_fusion_strflag_conv_cps.c \
            ./srcs/ft_printf/ptf_fusion_strflag_conv_dius.c \
            ./srcs/ft_printf/ptf_fusion_strflag_conv_s_utils.c \
            ./srcs/ft_printf/ptf_init_flags.c \
            ./srcs/ft_printf/ptf_join_width_preci.c \
            ./srcs/ft_printf/ptf_start_fusion.c \
            ./srcs/ft_printf/ptf_utils.c \
            ./srcs/ft_printf/ptf_utils_itoa.c \
            ./srcs/ft_printf/ptf_utils_size.c

IDIR	=	./includes/

OBJS	=	${SRCS:.c=.o}

CC		=	clang

CFLAGS	=	-Wall -Wextra -Werror -I ${IDIR}

LIBC	=	ar rc

LIBR	=	ranlib

RM		=	rm -f

all:		
			@echo "Starting libft build."
			@ make ${NAME}

${NAME}:	${OBJS} ${IDIR}
			@${LIBC} ${NAME} ${OBJS}
			@${LIBR} ${NAME}
			@echo "Libft is ready to be used !"

.c.o:
			@${CC} ${CFLAGS} -c $< -o $@

clean:
			@${RM} ${OBJS}
			@echo "Rule clean done."

fclean:		clean
			@${RM} ${NAME}
			@echo "Rule fclean done."

re:			fclean all

.PHONY: 	all clean fclean re