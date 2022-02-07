# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 10:44:41 by ldermign          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/02/07 14:10:15 by ejahan           ###   ########.fr        #
=======
#    Updated: 2022/02/07 16:04:44 by ldermign         ###   ########.fr        #
>>>>>>> liena
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

INCS	=	./incs/

SRCS	=	./srcs/main.c \
			./srcs/built_in.c \
			./srcs/supprimer.c \
			./srcs/get_env.c \
			./srcs/uts_split_ms.c \
			./srcs/uts_built_in.c \
			./srcs/cmd_redirection.c \
			./srcs/built_in_pwd_cd_echo.c \
			./srcs/built_in_exit_unset_env.c \
			./srcs/uts_list_var_env_ms.c \
			./srcs/parsing/command/echo2.c ./srcs/parsing/command/cd_pwd.c \
			./srcs/parsing/command/command.c ./srcs/parsing/command/env.c \
			./srcs/parsing/command/export.c ./srcs/parsing/command/unset.c \
			./srcs/parsing/error.c ./srcs/parsing/parsing.c \
			./srcs/parsing/redirections/redirections_tst.c \
			./srcs/parsing/redirections/redirection1.c \
			./srcs/parsing/redirections/redirection2.c \
			./srcs/parsing/redirections/redirection3.c \
			./srcs/parsing/redirections/redirection4.c \
			./srcs/parsing/command/echo_tst.c

OBJS	=	${SRCS:.c=.o}

DEPS	=	${SRCS:.c=.d}

CC		=	clang

RM		=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror -I ${INCS}

all:		${NAME}

${NAME}:	${OBJS}
			@${MAKE} -C ./libft
			@${CC} -o ${NAME} ${OBJS} ${CFLAGS} -fsanitize=address -lreadline libft/libft.a

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