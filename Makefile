# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elisa <elisa@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 10:44:41 by ldermign          #+#    #+#              #
#    Updated: 2022/01/18 15:56:43 by elisa            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

INCS	=	./incs/

SRCS	=	./srcs/main.c \
			./srcs/built_in.c \
			./srcs/supprimer.c \
			./srcs/get_env.c \
			./srcs/uts_split_ms.c \
			./srcs./parsing/command/echo.c ./srcs/parsing/command/cd_pwd.c \
			./srcs/parsing/command/command.c ./srcs/parsing/command/env.c \
			./srcs/parsing/command/export.c ./srcs/parsing/command/unset.c \
			./srcs/parsing/error.c ./srcs/parsing/parsing.c

OBJS	=	${SRCS:.c=.o}

DEPS	=	${SRCS:.c=.d}

CC		=	clang

RM		=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror -I ${INCS}

all:		${NAME}

${NAME}:	${OBJS}
			@${MAKE} -C ./libft
			@${CC} -o ${NAME} ${OBJS} ${CFLAGS} -lreadline libft/libft.a

-include	${DEPS}

%.o:%.c
			@${CC} ${CFLAGS} -o $@ -c $<
			@${CC} ${CFLAGS} -MMD -MP -MF ${@:.o=.d} -o $@ -c $<

clean:
			${MAKE} -C libft clean
			${RM} ${OBJS} ${DEPS}

fclean:		clean
			${MAKE} -C libft fclean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re