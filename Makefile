GREEN  		= \033[0;32m
YELLOW 		= \033[0;33m
RED    		= \033[0;31m
RESET  		= \033[0m
BOLD		= \033[1m
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
			  src/init.c \
			  src/signals/signals.c \
			  src/prompt/prompt_utils.c \
			  src/execution/main.c \
			  src/execution/utils.c \
			  src/execution/redirections/redirections.c \
			  src/execution/redirections/redirections_utils.c \
			  src/execution/environ/make_env.c \
			  src/execution/environ/env_utils.c \
			  src/execution/environ/env_actions.c \
			  src/execution/exec/pipeline.c \
			  src/execution/exec/compound_command.c \
			  src/execution/exec/simple_command.c \
			  src/execution/exec/subshell.c \
			  src/execution/builtins/cd.c \
			  src/execution/builtins/echo.c \
			  src/execution/builtins/pwd.c \
			  src/execution/builtins/export.c \
			  src/execution/builtins/unset.c \
			  src/execution/builtins/env.c \
			  src/execution/builtins/exit.c \
			  src/execution/builtins/utils.c \
			  src/execution/builtins/export_utils.c \
			  src/execution/expand/build_mask.c \
			  src/execution/expand/expand_var.c \
			  src/execution/expand/expand_conditons.c \
			  src/execution/expand/expand_wildcard_at_str.c \
			  src/execution/expand/extract_args.c \
			  src/execution/expand/get_name_value.c \
			  src/execution/expand/split_input.c \
			  src/execution/expand/wildcard.c \
			  src/execution/expand/wildcard_utils.c \
			  src/execution/expand/expand_heredoc.c \
			  src/execution/expand/expand_filename.c \
			  src/parsing/main.c \
			  src/parsing/ast_functions.c \
			  src/parsing/tokenizing/tokenizing_utils.c \
			  src/parsing/tokenizing/tokenizing.c \
			  src/parsing/ast/build_ast.c \
			  src/parsing/ast/parsing_utils_1.c \
			  src/parsing/ast/parsing_utils_2.c \
			  src/parsing/ast/syn_err.c \
			  src/parsing/heredoc/run_heredoc.c \
			  src/parsing/heredoc/generate_file_name.c \
			  src/freeing/free_all_ast.c \
			  src/freeing/free.c
OBJ			= $(patsubst src/%.c, obj/%.o, $(SRC))
all: $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME) done!$(RESET)"

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(CLEAR)$(YELLOW)linking $(NAME)...$(RESET)"
	@$(CC) $(OBJ) $(LFLAGS) $(LIBFT) -o $(NAME)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo "[$(GREEN)$(BOLD) OK $(RESET)$(BOLD)]$(RESET) compiling $(BOLD)$@...$(RESET)$(CLEAR)"
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
