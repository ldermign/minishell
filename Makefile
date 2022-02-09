# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 10:44:41 by ldermign          #+#    #+#              #
#    Updated: 2022/02/09 08:44:47 by ldermign         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

INCS	=	./incs/

SRCS	=	./srcs/main.c \
			./srcs/exec/built_in.c ./srcs/exec/get_env.c \
			./srcs/exec/redirections.c ./srcs/exec/built_in_pwd_cd_echo.c \
			./srcs/exec/built_in_exit_unset_env.c \
			./srcs/utils/uts_split_ms.c ./srcs/utils/uts_built_in.c \
			./srcs/utils/uts_list_var_env_ms.c \
			./srcs/supprimer.c \
			./srcs/parsing/command/echo2.c ./srcs/parsing/command/cd_pwd.c \
			./srcs/parsing/command/command.c ./srcs/parsing/command/env.c \
			./srcs/parsing/command/export.c ./srcs/parsing/command/unset.c \
			./srcs/parsing/error.c ./srcs/parsing/parsing.c \
			./srcs/parsing/redirections/redirections.c \
			./srcs/parsing/redirections/redirection1.c \
			./srcs/parsing/redirections/redirection2.c \
			./srcs/parsing/redirections/redirection3.c \
			./srcs/parsing/redirections/redirection4.c \
			./srcs/parsing/command/echo.c ./srcs/parsing/command/fill_echo.c

OBJS	=	${SRCS:.c=.o}

DEPS	=	${SRCS:.c=.d}

CC		=	clang

RM		=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror -I ${INCS}

all:		${NAME}

${NAME}:	${OBJS}
			@${MAKE} -C ./libft
			@${CC} -o ${NAME} ${OBJS} -g3 ${CFLAGS} -lreadline libft/libft.a

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