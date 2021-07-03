NAME := minishell

SRC := gnl/get_next_line.c gnl/get_next_line_utils.c main.c lexer.c ft_split_cmd_args.c \
		ft_split_utils.c cmd_table.c test_list/print_list_str_array.c test_list/print_str_array.c
		

OBJ := $(patsubst %.c, %.o, $(SRC))

CC := gcc -g

FLAGS := -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

LIBFT := libft.a

$(NAME) :		$(LIBFT) $(OBJ) parser.h
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT) : 
	@$(MAKE) -C libft
	@mv libft/$(LIBFT) .

clean :
	@$(MAKE) -C libft clean
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME) $(LIBFT) a.out

re : fclean all

.PHONY:			all clean fclean re

test :	
	gcc -g ft_split_cmd_args.c ft_split_utils.c libft.a

test_print : $(LIBFT) $(OBJ) parser.h
	$(CC) $(FLAGS) $(OBJ) $(LIBFT)


leak:
	export MallocStackLoggingNoCompact=1