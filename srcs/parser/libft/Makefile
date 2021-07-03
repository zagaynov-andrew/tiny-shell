NAME = libft.a

SRC = ft_atoi.c \
			ft_itoa.c \
			ft_putchar.c \
			ft_strdup.c	\
			ft_strrchr.c \
			ft_bzero.c \
			ft_putchar_fd.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_calloc.c \
			ft_memccpy.c \
			ft_putendl_fd.c \
			ft_strlcat.c \
			ft_substr.c \
			ft_isalnum.c \
			ft_memchr.c \
			ft_putnbr_fd.c \
			ft_strlcpy.c \
			ft_tolower.c \
			ft_isalpha.c \
			ft_memcmp.c \
			ft_putstr.c \
			ft_strlen.c \
			ft_toupper.c \
			ft_isdigit.c \
			ft_memmove.c \
			ft_split.c \
			ft_strncmp.c \
			ft_isprint.c \
			ft_memset.c \
			ft_strchr.c	 \
			ft_strnstr.c \
			ft_isascii.c \
			ft_memcpy.c	\
			ft_putstr_fd.c \
			ft_strmapi.c \
			ft_strncpy.c

SRC_BONUS = ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c

OBJ = $(patsubst %.c, %.o, $(SRC))
OBJ_BONUS = $(patsubst %.c, %.o, $(SRC_BONUS))

override OBJ_ALL = $(OBJ) $(OBJ_BONUS)

CC = gcc
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_ALL) $(OBJ)
	ar rcs $(NAME) $?
	ranlib $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_BONUS) $(OBJ)

fclean: clean
	rm -f $(NAME)
re: fclean all

bonus:
	@make OBJ_ALL="$(OBJ) $(OBJ_BONUS)" all

.PHONY: all bonus clean fclean re