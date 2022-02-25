NAME			= tinyshell
TINYLIBC_DIR	= libs/tinylibc
PARSER_DIR		= parser/
EXECUTOR_DIR	= executor/
BUILTIN_DIR		= builtin/
TEST_DIR		= test/
SRCS_DIR		= ./srcs/
OBJS_DIR		= objs/
CC				= gcc
CC_FLAGS		= -Wall -Wextra -Werror

SRCS	=	$(SRCS_DIR)$(EXECUTOR_DIR)executor.c			\
			$(SRCS_DIR)$(EXECUTOR_DIR)executor_utils.c		\
			$(SRCS_DIR)$(EXECUTOR_DIR)shell_lvl.c			\
			$(SRCS_DIR)$(EXECUTOR_DIR)fd_substitution.c		\
			$(SRCS_DIR)$(EXECUTOR_DIR)pre_execution.c		\
			$(SRCS_DIR)$(BUILTIN_DIR)echo.c					\
			$(SRCS_DIR)$(BUILTIN_DIR)pwd.c					\
			$(SRCS_DIR)$(BUILTIN_DIR)cd.c					\
			$(SRCS_DIR)$(BUILTIN_DIR)cd_utils.c				\
			$(SRCS_DIR)$(BUILTIN_DIR)env.c					\
			$(SRCS_DIR)$(BUILTIN_DIR)env_var_utils.c		\
			$(SRCS_DIR)$(BUILTIN_DIR)export.c				\
			$(SRCS_DIR)$(BUILTIN_DIR)export_utils.c			\
			$(SRCS_DIR)$(BUILTIN_DIR)unset.c				\
			$(SRCS_DIR)$(BUILTIN_DIR)exit.c					\
			$(SRCS_DIR)$(TEST_DIR)print_str_array.c			\
			$(SRCS_DIR)$(TEST_DIR)print_list_str_array.c	\
			$(SRCS_DIR)$(TEST_DIR)msh_errors.c				\
			$(SRCS_DIR)$(TEST_DIR)msh_errors_utils.c		\
			$(SRCS_DIR)$(TEST_DIR)msh_signals.c				\
			$(SRCS_DIR)$(TEST_DIR)msh_heredoc.c				\
			$(SRCS_DIR)$(PARSER_DIR)lexer.c					\
			$(SRCS_DIR)$(PARSER_DIR)lexer_utils.c			\
			$(SRCS_DIR)$(PARSER_DIR)ft_split_cmd_args.c		\
			$(SRCS_DIR)$(PARSER_DIR)check_var.c				\
			$(SRCS_DIR)$(PARSER_DIR)ft_error.c				\
			$(SRCS_DIR)$(PARSER_DIR)check_cmd.c				\
			$(SRCS_DIR)$(PARSER_DIR)check_cmd_utils.c		\
			$(SRCS_DIR)$(PARSER_DIR)ft_split_utils.c		\
			$(SRCS_DIR)$(PARSER_DIR)ft_split_utils_2.c		\
			$(SRCS_DIR)$(PARSER_DIR)cmd_table.c				\
			$(SRCS_DIR)$(PARSER_DIR)cmd_table_utils.c		\
			$(SRCS_DIR)$(PARSER_DIR)parse_line.c			\
			$(SRCS_DIR)$(PARSER_DIR)parse_line_utils.c		\
			$(SRCS_DIR)$(PARSER_DIR)replace_var.c			\
			$(SRCS_DIR)$(PARSER_DIR)preparser.c				\
			$(SRCS_DIR)$(PARSER_DIR)preparser_utils.c		\
			$(SRCS_DIR)$(PARSER_DIR)preparser_utils_2.c		\
			$(SRCS_DIR)split_shell_lst.c					\
			$(SRCS_DIR)prompt_loop.c						\
			$(SRCS_DIR)split_shell_lst_utils.c				\
			$(SRCS_DIR)tinyshell.c

OBJS			= $(notdir $(SRCS:.c=.o))
OBJS_PATH		= $(addprefix $(OBJS_DIR), $(OBJS))


$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(SRCS_DIR)tinyshell.h
	@mkdir -p $(OBJS_DIR)
	@echo "\033[0;32m- Done :\033[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@ -I./libs/readline/include

$(OBJS_DIR)%.o : $(SRCS_DIR)$(TEST_DIR)%.c $(SRCS_DIR)$(TEST_DIR)test_tinyshell.h
	@mkdir -p $(OBJS_DIR)
	@echo "\033[0;32m- Done :\033[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR)%.o : $(SRCS_DIR)$(PARSER_DIR)%.c $(SRCS_DIR)$(PARSER_DIR)parser.h
	@mkdir -p $(OBJS_DIR)
	@echo "\033[0;32m- Done :\033[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR)%.o : $(SRCS_DIR)$(EXECUTOR_DIR)%.c $(SRCS_DIR)$(EXECUTOR_DIR)executor.h
	@mkdir -p $(OBJS_DIR)
	@echo "\033[0;32m- Done :\033[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR)%.o : $(SRCS_DIR)$(BUILTIN_DIR)%.c $(SRCS_DIR)$(BUILTIN_DIR)builtin.h
	@mkdir -p $(OBJS_DIR)
	@echo "\033[0;32m- Done :\033[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJS_PATH)
	@$(MAKE) full -C $(TINYLIBC_DIR)
	@gcc -o $(NAME) libs/tinylibc/tinylibc.a $(OBJS_PATH) -lreadline -L ./libs/readline/lib
	@echo "✅✅✅ \033[0;30;42mTINYSHELL IS COMPLETED\033[0m ✅✅✅"

all: $(NAME)

clean:
	@$(MAKE) clean -C $(TINYLIBC_DIR)
	rm -Rf $(OBJS_DIR)

fclean: clean
	@$(MAKE) fclean -C $(TINYLIBC_DIR)
	rm -f $(NAME)

re: fclean all

bonus: $(NAME)

.PHONY : all clean fclean re bonus
