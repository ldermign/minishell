# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 10:44:41 by ldermign          #+#    #+#              #
#    Updated: 2022/03/04 00:26:18 by ejahan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

INCS	=	./incs/

SRCS	=	./srcs/main.c \
			./srcs/exec/built_in.c ./srcs/exec/get_env.c \
			./srcs/exec/redirections.c ./srcs/exec/built_in_pwd_cd_echo.c \
			./srcs/exec/built_in_exit_unset_env.c ./srcs/exec/pipe.c \
			./srcs/utils/uts_split_ms.c ./srcs/utils/uts_built_in.c \
			./srcs/utils/uts_list_var_env_ms.c ./srcs/utils/uts_redir.c \
			./srcs/exec/execute_cmd.c \
			./srcs/utils/uts_redir_2.c \
			./srcs/init/init_struct.c \
			./srcs/supprimer.c \
			./srcs/parsing/parsing.c ./srcs/parsing/initialisations.c\
			./srcs/parsing/lists.c ./srcs/parsing/sep_args.c \
			./srcs/parsing/recup_pipe.c ./srcs/parsing/count_arg.c \
			./srcs/parsing/utils.c ./srcs/parsing/empty_args.c \
			./srcs/parsing/len_arg.c ./srcs/parsing/len_variable.c \
			./srcs/parsing/fill_variable.c ./srcs/parsing/fill_arg.c \
			./srcs/parsing/echo.c ./srcs/parsing/list_ok.c \
			./srcs/parsing/recup_redir.c ./srcs/parsing/signals.c

OBJS	=	${SRCS:.c=.o}

DEPS	=	${SRCS:.c=.d}

CC		=	clang

RM		=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror -I ${INCS} -g3

all:		${NAME}

${NAME}:	${OBJS}
			@${MAKE} -C ./libft
			@${CC} -o ${NAME} ${OBJS}  ${CFLAGS} -lreadline libft/libft.a

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
