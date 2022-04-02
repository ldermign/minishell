# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 10:44:41 by ldermign          #+#    #+#              #
#    Updated: 2022/04/02 11:32:22 by ldermign         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

INCS	=	./incs/

SRCS	=	./srcs/main.c \
			./srcs/exec/execve.c \
			./srcs/exec/others_executables.c \
			./srcs/built_in/built_in.c \
			./srcs/built_in/built_in_pwd_echo.c \
			./srcs/built_in/built_in_unset_env.c \
			./srcs/built_in/built_in_export.c \
			./srcs/built_in/built_in_cd.c \
			./srcs/built_in/built_in_exit.c \
			./srcs/built_in/uts_built_in_export_1.c \
			./srcs/built_in/uts_built_in_export_2.c \
			./srcs/redirections/redirections.c \
			./srcs/redirections/uts_redir_1.c \
			./srcs/redirections/uts_redir_2.c \
			./srcs/redirections/uts_redir_3.c \
			./srcs/pipe/pipe.c \
			./srcs/pipe/uts_pipe.c \
			./srcs/utils/uts_split_ms.c \
			./srcs/utils/uts_start_list_var_env_ms.c \
			./srcs/utils/uts_list_var_env_ms.c \
			./srcs/utils/get_env.c \
			./srcs/init_free/init_struct.c \
			./srcs/init_free/init.c \
			./srcs/init_free/free.c \
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
			./srcs/parsing/files_redir.c ./srcs/parsing/arg_list.c \
			./srcs/parsing/free_hd.c ./srcs/parsing/ctrl_d.c \
			./srcs/parsing/utils_here_doc.c ./srcs/parsing/utils_recup_hd.c 

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
			@${MAKE} -C libft clean
			@${RM} ${OBJS} ${DEPS}

fclean:		clean
			@${MAKE} -C libft fclean
			@${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
