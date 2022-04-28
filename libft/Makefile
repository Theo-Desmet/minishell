# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/05 21:33:20 by bbordere          #+#    #+#              #
#    Updated: 2022/03/05 21:33:20 by bbordere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES = includes/

FILES_STR = ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
			ft_strnstr.c ft_atoi.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c \
			ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_strcpy.c \
			ft_strcmp.c ft_strstr.c ft_strreplace.c ft_strcat.c ft_atol.c ft_strcapitalize.c \
			ft_get_index.c

FILES_IS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_isspace.c

FILES_LST = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstlast.c ft_lstiter.c ft_lstmap.c

FILES_MEM = ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_calloc.c ft_free_tab.c ft_realloc.c

FILES_FT_PRINTF = ft_printf.c ft_printf_utils.c

FILES_GNL = get_next_line.c

SRCS_STR = $(addprefix src/ft_str/, $(FILES_STR))
SRCS_IS = $(addprefix src/ft_is/, $(FILES_IS))
SRCS_LST = $(addprefix src/ft_lst/, $(FILES_LST))
SRCS_MEM = $(addprefix src/ft_mem/, $(FILES_MEM))
SRCS_FT_PRINTF = $(addprefix src/ft_printf/, $(FILES_FT_PRINTF))
SRCS_GNL = $(addprefix src/get_next_line/, $(FILES_GNL))

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES)

OBJ = $(SRCS_STR:.c=.o) $(SRCS_IS:.c=.o) $(SRCS_LST:.c=.o) $(SRCS_MEM:.c=.o) $(SRCS_FT_PRINTF:.c=.o) $(SRCS_GNL:.c=.o)

NAME = libft.a

$(NAME): $(OBJ)
	@ ar rcs $(NAME) $(OBJ)

all: $(NAME)

clean:
	@ rm -f $(OBJ)

fclean : clean
	@ rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT: $(OBJ)