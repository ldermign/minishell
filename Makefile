# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 10:44:41 by ldermign          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/03/14 08:33:35 by ldermign         ###   ########.fr        #
=======
#    Updated: 2022/03/14 06:24:52 by ejahan           ###   ########.fr        #
>>>>>>> 832e480ccc085e91f236216d921934a5e02b55b3
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
			./srcs/utils/free.c ./srcs/exec/built_in_pipe.c \
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
			./srcs/parsing/echo.c ./srcs/parsing/list_hd.c \
			./srcs/parsing/recup_redir.c ./srcs/parsing/signals.c \
			./srcs/parsing/error_malloc.c ./srcs/parsing/len_variable2.c \
			./srcs/parsing/free.c ./srcs/parsing/here_doc.c \
			./srcs/parsing/files_redir.c ./srcs/parsing/arg_list.c

OBJS	=	${SRCS:.c=.o}

DEPS	=	${SRCS:.c=.d}

CC		=	clang

RM		=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror -I ${INCS} -g3 #-fsanitize=address

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
