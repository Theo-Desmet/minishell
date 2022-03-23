NAME = minishell

SRC =	./src/main.c\

LIB_PATH = libft/

CC = @clang

CFLAGS = -g #-Wall -Werror -Wextra

OBJ = $(SRC:.c=.o)

%.o:%.c fdf.h
	@$(CC) $(CFLAGS) -O3 -c $< -o $@

all: subsystem $(NAME)

subsystem:
	@cd $(LIB_PATH) && make all

$(NAME): begin $(OBJ)
	@make -C $(LIB_PATH) all
	$(CC) $(OBJ)  libft/libft.a -o $(NAME)
	@echo "\033[;32mcompilation de fdf terminée\033[0m"

#@$(CC) $(OBJ) $(LIB_PATH)libft.a -o $(NAME)

clean:
	@make -C $(LIB_PATH) fclean
	@rm -f $(OBJ)
	@echo "\033[;31msuppression des fichiers *.o de fdf\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[;31msuppression de l'executable fdf\033[0m"

re: fclean all

begin:
	@echo "\033[;32mdebut de la compilation de fdf\033[0m"

.PHONY: all clean fclean re

