# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 10:44:41 by ldermign          #+#    #+#              #
#    Updated: 2022/03/01 18:22:10 by ejahan           ###   ########.fr        #
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
			./srcs/new_parsing/parsing.c ./srcs/new_parsing/initialisations.c\
			./srcs/new_parsing/lists.c ./srcs/new_parsing/sep_args.c \
			./srcs/new_parsing/recup_pipe.c ./srcs/new_parsing/count_arg.c \
			./srcs/new_parsing/utils.c ./srcs/new_parsing/empty_args.c \
			./srcs/new_parsing/len_arg.c ./srcs/new_parsing/len_variable.c \
			./srcs/new_parsing/fill_variable.c ./srcs/new_parsing/fill_arg.c \
			./srcs/new_parsing/echo.c ./srcs/new_parsing/list_ok.c \
			# ./srcs/new_parsing/recup_redir.c \
			# ./srcs/parsing/utils.c ./srcs/parsing/command/commands2.c \
			# ./srcs/parsing/command/commands.c \
			# ./srcs/parsing/command/fill_echo.c ./srcs/parsing/command/echo.c \
			# ./srcs/parsing/error.c ./srcs/parsing/parsing.c \
			# ./srcs/parsing/redirections/redirections.c \
			# ./srcs/parsing/redirections/redirection1.c \
			# ./srcs/parsing/redirections/redirection2.c \
			# ./srcs/parsing/redirections/redirection3.c \
			# ./srcs/parsing/redirections/redirection4.c

OBJS	=	${SRCS:.c=.o}

DEPS	=	${SRCS:.c=.d}

CC		=	clang

RM		=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror -I ${INCS} -g3 -fsanitize=address

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
