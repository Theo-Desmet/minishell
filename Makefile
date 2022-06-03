# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/18 21:36:22 by bbordere          #+#    #+#              #
#    Updated: 2022/05/30 13:48:35 by tdesmet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -g3 -I includes/ -Wall -Werror -Wextra

FILES = $(wildcard builtin/*.c) $(wildcard lexer/*.c) $(wildcard parser/*.c) $(wildcard expansions/*.c) main.c cleaning.c init.c utils.c signal.c

OBJS = $(FILES:.c=.o)

%.o: %.c
	@printf "\033[0;33mCompiling camarade: %-33.33s\r" $@
	@$(CC) $(CFLAGS) -c $< -o $@

NAME = minishell

$(NAME): $(OBJS)
	@ $(MAKE) -C libft all --no-print-directory
	@ $(CC) $(CFLAGS) $(OBJS) -lreadline libft/libft.a  -o  $(NAME) 
	@ printf '\033[0;32mWELCOME TO THE GULAG !!!                \033[0m\n'
	@ echo  "                                 \033[5;38;2;251;208;54m  █                                                "
	@ echo  "                                 \033[5;38;2;251;208;54m ███                                               "
	@ echo  "\033[0;38;2;186;11;24m  ██████╗ ██╗   ██╗██████╗  \033[5;38;2;251;208;54m▄▄▄▄▄█████▄▄▄▄▄\033[0;38;2;186;11;24m  ███████╗██╗  ██╗███████╗██╗     ██╗     "
	@ echo  "\033[0;38;2;186;11;24m ██╔═══██╗██║   ██║██╔══██╗  \033[5;38;2;251;208;54m▀███████████▀ \033[0;38;2;186;11;24m  ██╔════╝██║  ██║██╔════╝██║     ██║     "
	@ echo  "\033[0;38;2;186;11;24m ██║   ██║██║   ██║██████╔╝   \033[5;38;2;251;208;54m ▀███████▀   \033[0;38;2;186;11;24m  ███████╗███████║█████╗  ██║     ██║     "
	@ echo  "\033[0;38;2;186;11;24m ██║   ██║██║   ██║██╔══██╗    \033[5;38;2;251;208;54m▄███▀███▄   \033[0;38;2;186;11;24m  ╚════██║██╔══██║██╔══╝  ██║     ██║     "	
	@ echo  "\033[0;38;2;186;11;24m ╚██████╔╝╚██████╔╝██║  ██║  \033[5;38;2;251;208;54m ▄██▀   ▀██▄  \033[0;38;2;186;11;24m  ███████║██║  ██║███████╗███████╗███████╗"
	@ echo  "\033[0;38;2;186;11;24m  ╚═════╝  ╚═════╝ ╚═╝  ╚═╝  \033[5;38;2;251;208;54m █▀       ▀█  \033[0;38;2;186;11;24m  ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\033[0m"


all: $(NAME)

clean:
	@ rm -f $(OBJS)
	@ $(MAKE) -C libft clean --no-print-directory
	@ printf '\033[0;32mclean done\033[0m\n'

fclean: clean
	@ rm -f $(NAME)
	@ $(MAKE) -C libft fclean --no-print-directory
	@ printf '\033[0;32mfclean done\033[0m\n'

re: fclean all

.PHONY: all clean fclean re

.SILENT: $(OBJS)
