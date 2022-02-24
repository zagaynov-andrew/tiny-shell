NAME = tinylibc.a
CC = gcc
CC_FLAGS = -Wall -Wextra -Werror

SRCS	=	ft_memset.c		\
			ft_bzero.c		\
			ft_memcpy.c		\
			ft_memccpy.c	\
			ft_memmove.c 	\
			ft_memchr.c		\
			ft_memcmp.c		\
			ft_strlen.c		\
			ft_isalpha.c 	\
			ft_isdigit.c	\
			ft_isalnum.c	\
			ft_isascii.c	\
			ft_isprint.c	\
			ft_toupper.c	\
			ft_tolower.c	\
			ft_strchr.c		\
			ft_strrchr.c	\
			ft_strncmp.c	\
			ft_strlcpy.c	\
			ft_strncpy.c	\
			ft_strlcat.c	\
			ft_strnstr.c	\
			ft_atoi.c		\
			ft_calloc.c		\
			ft_strdup.c		\
			ft_substr.c		\
			ft_strjoin.c 	\
			ft_strtrim.c	\
			ft_split.c		\
			ft_itoa.c		\
			ft_strmapi.c	\
			ft_putchar_fd.c	\
			ft_putstr_fd.c	\
			ft_putendl_fd.c	\
			ft_putnbr_fd.c	\
			ft_putnstr_fd.c	\
			ft_abs.c		\
			ft_llitoa.c		\
			ft_itoa_base.c	\
			ft_strupcase.c	\
			ft_strcmp.c		\
			ft_str_is_empty.c		\
			ft_lli_len.c			\
			ft_is_whitespace.c

SRCS_VEC	=	ft_vec/ft_vec_new.c		\
				ft_vec/ft_vec_push.c	\
				ft_vec/ft_vec_free.c	\
				$(SRCS)

SRCS_STR_ARRAY	=	str_array/str_array_sort.c		\
					str_array/str_array_size.c		\
					str_array/str_array_free.c		\
					str_array/str_array_copy.c		\
					str_array/str_array_add_back.c	\
					str_array/str_array_erase.c	\
					$(SRCS)

SRCS_LIST	=	ft_list/ft_lstnew.c			\
				ft_list/ft_lstadd_front.c	\
				ft_list/ft_lstsize.c		\
				ft_list/ft_lstlast.c		\
				ft_list/ft_lstadd_back.c	\
				ft_list/ft_lstclear.c		\
				ft_list/ft_lstdelone.c		\
				ft_list/ft_lstiter.c		\
				ft_list/ft_lstmap.c			\
				ft_list/ft_lst_to_array.c	\
				$(SRCS)

OBJS_DIR = objs/
OBJS = $(notdir $(SRCS:.c=.o))
OBJS_PATH = $(addprefix $(OBJS_DIR), $(OBJS))
OBJS_VEC = $(notdir $(SRCS_VEC:.c=.o))
OBJS_VEC_PATH = $(addprefix $(OBJS_DIR), $(OBJS_VEC))
OBJS_LIST = $(notdir $(SRCS_LIST:.c=.o))
OBJS_LIST_PATH = $(addprefix $(OBJS_DIR), $(OBJS_LIST))
OBJS_STR_ARRAY = $(notdir $(SRCS_STR_ARRAY:.c=.o))
OBJS_STR_ARRAY_PATH = $(addprefix $(OBJS_DIR), $(OBJS_STR_ARRAY))


$(OBJS_DIR)%.o : %.c tinylibc.h
	@mkdir -p $(OBJS_DIR)
	@echo "\033[1;31m- Done :\033[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR)%.o : ft_vec/%.c tinylibc.h
	@mkdir -p $(OBJS_DIR)
	@echo "\033[1;31m- Done :\033[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR)%.o : ft_list/%.c tinylibc.h
	@mkdir -p $(OBJS_DIR)
	@echo "\033[1;31m- Done :\033[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR)%.o : str_array/%.c str_array/str_array.h
	@mkdir -p $(OBJS_DIR)
	@echo "\033[1;31m- Done :\033[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJS_PATH)
	@ar r $(NAME) $(OBJS_PATH)
	@echo "🔥🔥🔥 \033[0;31;43mtinylibc IS COMPLETED\033[0m 🔥🔥🔥"

all: $(NAME)

clean:
	rm -Rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

vec: $(OBJS_VEC_PATH)
	@ar r $(NAME) $(OBJS_VEC_PATH)
	@echo "🔥🔥🔥 \033[0;31;43mtinylibc WITH VEC IS COMPLETED\033[0m 🔥🔥🔥"

list: $(OBJS_LIST_PATH)
	@ar r $(NAME) $(OBJS_LIST_PATH)
	@echo "🔥🔥🔥 \033[0;31;43mtinylibc WITH LIST IS COMPLETED\033[0m 🔥🔥🔥"

str_array: $(OBJS_STR_ARRAY_PATH)
	@ar r $(NAME) $(OBJS_STR_ARRAY_PATH)
	@echo "🔥🔥🔥 \033[0;31;43mtinylibc WITH STR_ARRAY IS COMPLETED\033[0m 🔥🔥🔥"

full:
	@make list vec str_array

.PHONY : $(NAME) all clean fclean re vec list
