MakeGREEN  		= \033[0;32m
YELLOW 		= \033[0;33m
RED    		= \033[0;31m
RESET  		= \033[0m
CLEAR		= \033[K\r
NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
LFLAGS		= -lreadline
AR			= ar rcs
INCLUDES	= -I./headers/ -I./libft/headers/
LIBFT_DIR	= libft
LIBFT		= $(addprefix $(LIBFT_DIR)/, libft.a)
SRC			= src/main.c \
			  src/free.c \
			  src/init.c \
			  src/execution/main.c \
			  src/execution/utils.c \
			  src/execution/make_env.c \
			  src/execution/pipeline.c \
			  src/execution/compound_command.c \
			  src/execution/simple_command.c \
			  src/execution/subshell.c \
			  src/execution/builtins/cd.c \
			  src/execution/builtins/echo.c \
			  src/execution/builtins/pwd.c \
			  src/execution/builtins/export.c \
			  src/execution/builtins/unset.c \
			  src/execution/builtins/env.c \
			  src/execution/builtins/exit.c \
			  src/execution/builtins/utils.c \
			  src/execution/builtins/export_utils.c \
			  src/execution/env_utils.c \
			  src/parsing/main.c \
			  src/parsing/test.c \
			  src/parsing/parsing.c \
			  src/parsing/ast_functions.c \
			  src/parsing/tokenizing.c \
			  src/parsing/parsing_utils_1.c \
			  src/parsing/parsing_utils_2.c \
			  src/parsing/expand.c \
			  src/parsing/tokenizing_utils.c
OBJ			= $(patsubst src/%.c, obj/%.o, $(SRC))
all: $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME) done!$(RESET)"

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(CLEAR)$(YELLOW)linking $(NAME)...$(RESET)"
	@$(CC) $(OBJ) $(LFLAGS) $(LIBFT) -o $(NAME)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo -n "$(YELLOW)complining $@...$(RESET)$(CLEAR)"
	@$(CC) -c $(CFLAGS) $< $(INCLUDES) -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)/ all

clean:
	@make -C $(LIBFT_DIR)/ clean
	@rm -rf obj

fclean: clean
	@make -C $(LIBFT_DIR)/ fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean
