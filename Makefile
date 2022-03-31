NAME = minishell

BUILTINS = cd env export pwd unset main init print_export echo

SRC =	$(addsuffix .c, $(addprefix builtin/, $(BUILTINS))) \

LIB_PATH = libft/

LIBFT = -L libft -lft

CC = clang

CFLAGS = -g3 #-Wall -Werror -Wextra

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n"
	@make -C $(LIB_PATH) all
	@echo "\033[;32mdebut de la compilation de minishell\033[0m"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "\033[;32mcompilation de minishell terminée\033[0m"

%.o: %.c
	@printf "\033[0;33mGeneration des objets de minishell minishell : %-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@make -C $(LIB_PATH) fclean
	@rm -f $(OBJ)
	@echo "\033[;31msuppression des fichiers *.o de minishell\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[;31msuppression de l'executable minishell\033[0m"

re: fclean all

.PHONY: all clean fclean re

