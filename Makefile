# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/15 17:10:51 by ngamora           #+#    #+#              #
#    Updated: 2021/06/30 15:16:17 by ngamora          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
LIBFT_DIR		= ./libft/
PARSER_DIR		= parser/
EXECUTOR_DIR	= executor/
TEST_DIR		= test/
SRCS_DIR		= ./srcs/
OBJS_DIR		= ./objs/
CC				= gcc
CC_FLAGS		= -g #-Wall -Wextra -Werror

LIBFT_SRCS	=	ft_memset.c				\
				ft_bzero.c				\
				ft_memcpy.c				\
				ft_memccpy.c			\
				ft_memmove.c 			\
				ft_memchr.c				\
				ft_memcmp.c				\
				ft_strlen.c				\
				ft_isalpha.c 			\
				ft_isdigit.c			\
				ft_isalnum.c			\
				ft_isascii.c			\
				ft_isprint.c			\
				ft_toupper.c			\
				ft_tolower.c			\
				ft_strchr.c				\
				ft_strrchr.c			\
				ft_strncmp.c			\
				ft_strlcpy.c			\
				ft_strlcat.c			\
				ft_strnstr.c			\
				ft_atoi.c				\
				ft_calloc.c				\
				ft_strdup.c				\
				ft_substr.c				\
				ft_strjoin.c 			\
				ft_strtrim.c			\
				ft_split.c				\
				ft_itoa.c				\
				ft_strmapi.c			\
				ft_putchar_fd.c			\
				ft_putstr_fd.c			\
				ft_putendl_fd.c			\
				ft_putnbr_fd.c			\
				ft_putnstr_fd.c			\
				ft_abs.c				\
				ft_llitoa.c				\
				ft_itoa_base.c			\
				ft_strupcase.c			\
				ft_strcmp.c				\
				ft_str_is_empty.c		\
				ft_lli_len.c			\
				ft_is_whitespace.c		\
				ft_list/ft_lstnew.c			\
				ft_list/ft_lstadd_front.c	\
				ft_list/ft_lstsize.c		\
				ft_list/ft_lstlast.c		\
				ft_list/ft_lstadd_back.c	\
				ft_list/ft_lstclear.c		\
				ft_list/ft_lstdelone.c		\
				ft_list/ft_lstiter.c		\
				ft_list/ft_lstmap.c			\
				ft_vec/ft_vec_new.c			\
				ft_vec/ft_vec_push.c		\
				ft_vec/ft_vec_free.c

SRCS	=	$(SRCS_DIR)$(EXECUTOR_DIR)executor.c			\
			$(SRCS_DIR)$(EXECUTOR_DIR)executor_utils.c		\
			$(SRCS_DIR)$(EXECUTOR_DIR)str_array_free.c		\
			$(SRCS_DIR)$(EXECUTOR_DIR)msh_file_creation.c	\
			$(SRCS_DIR)$(TEST_DIR)print_str_array.c			\
			$(SRCS_DIR)$(TEST_DIR)print_list_str_array.c	\
			$(SRCS_DIR)minishell.c

OBJS			= $(notdir $(SRCS:.c=.o))
OBJS_PATH		= $(addprefix $(OBJS_DIR), $(OBJS))
LIBFT_OBJ_PATH	= $(addprefix $(LIBFT_DIR)$(OBJS_DIR), $(notdir $(LIBFT_SRCS:.c=.o)))

$(LIBFT_DIR)$(OBJS_DIR)%.o : $(LIBFT_DIR)%.c $(LIBFT_DIR)libft.h
	@$(MAKE) full -C $(LIBFT_DIR)
$(LIBFT_DIR)$(OBJS_DIR)%.o : $(LIBFT_DIR)ft_vec/%.c $(LIBFT_DIR)libft.h
	@$(MAKE) full -C $(LIBFT_DIR)
$(LIBFT_DIR)$(OBJS_DIR)%.o : $(LIBFT_DIR)ft_list/%.c $(LIBFT_DIR)libft.h
	@$(MAKE) full -C $(LIBFT_DIR)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@echo "\033[1;31m- Done :\033[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

# $(OBJS_DIR)%.o : $(SRCS_DIR)$(PARSER_DIR)%.c $(SRCS_DIR)minishell.h
# 	@mkdir -p $(OBJS_DIR)
# 	@echo "\033[1;31m- Done :\033[0m $<"
# 	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR)%.o : $(SRCS_DIR)$(TEST_DIR)%.c $(SRCS_DIR)$(TEST_DIR)test_minishell.h
	@mkdir -p $(OBJS_DIR)
	@echo "\033[1;31m- Done :\033[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR)%.o : $(SRCS_DIR)$(EXECUTOR_DIR)%.c $(SRCS_DIR)$(EXECUTOR_DIR)executor.h
	@mkdir -p $(OBJS_DIR)
	@echo "\033[1;31m- Done :\033[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(LIBFT_OBJ_PATH) $(OBJS_PATH)
	@gcc -o $(NAME) $(LIBFT_OBJ_PATH) $(OBJS_PATH)
	@echo "\033[1;31;42m=====minishell IS COMPLETED======\033[0m\n"

all: $(NAME)

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	rm -Rf $(OBJS_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
