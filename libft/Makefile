GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
RESET		= \033[0m
CLEAR		= \033[K\r
NAME		= libft.a
INCLUDES	= -I./headers
CC			= cc -c -Wall -Wextra -Werror
AR			= ar rcs
SRC			= src/ft_isalnum.c \
			  src/ft_isalpha.c \
			  src/dynamic_arr.c \
			  src/ft_isascii.c \
			  src/ft_isdigit.c \
			  src/ft_isprint.c \
			  src/ft_itoa.c \
			  src/ft_atof.c \
			  src/ft_atoi.c \
			  src/ft_atol.c \
			  src/ft_bzero.c \
			  src/ft_calloc.c \
			  src/ft_memchr.c \
			  src/ft_memcmp.c \
			  src/ft_memcpy.c \
			  src/ft_strisnum.c \
			  src/ft_strndup.c \
			  src/ft_memmove.c \
			  src/ft_memset.c \
			  src/ft_putchar_fd.c \
			  src/ft_putendl_fd.c \
			  src/ft_putnbr_fd.c \
			  src/ft_putstr_fd.c \
			  src/ft_split.c \
			  src/ft_strisempty.c \
			  src/ft_strisdecimal.c \
			  src/ft_strchr.c \
			  src/ft_strdup.c \
			  src/ft_striteri.c \
			  src/ft_strjoin.c \
			  src/ft_strlcat.c \
			  src/ft_strlcpy.c \
			  src/ft_strlen.c \
			  src/ft_strmapi.c \
			  src/ft_strncmp.c \
			  src/ft_strnstr.c \
			  src/ft_strrchr.c \
			  src/ft_strtrim.c \
			  src/ft_substr.c \
			  src/ft_tolower.c \
			  src/ft_strcmp.c \
			  src/ft_toupper.c \
			  src/ft_lstadd_back.c \
			  src/ft_lstadd_front.c \
			  src/ft_lstclear.c \
			  src/ft_lstpush.c \
			  src/ft_lstswap.c \
			  src/ft_lstrotate.c \
			  src/ft_lstreverse_rotate.c \
			  src/ft_lstdelone.c \
			  src/ft_lstiter.c \
			  src/ft_lstlast.c \
			  src/ft_lstmap.c \
			  src/ft_lstnew.c \
			  src/ft_lstsize.c \
			  src/ft_tokenize.c \
			  src/ft_execvpe.c \
			  src/ft_getenv.c \
			  src/ft_getpath.c \
			  src/ft_free_vector.c \
			  src/ft_printf/ft_printf_bonus.c \
			  src/ft_printf/parsing.c \
			  src/ft_printf/print_char.c \
			  src/ft_printf/print_hex.c \
			  src/ft_printf/print_nbr.c \
			  src/ft_printf/print_ptr.c \
			  src/ft_printf/print_str.c \
			  src/ft_printf/print_unsigned.c \
			  src/ft_printf/utils.c
OBJ			= $(patsubst src/%.c, obj/%.o, $(SRC))
RM			= rm -rf

all: $(NAME)


$(NAME): $(OBJ)
	@echo "$(CLEAR)$(GREEN)$(BOLD)Libft.a done!$(RESET)"

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $< $(INCLUDES) -o $@
	@echo -n "$(YELLOW)	inserting $@...$(RESET)$(CLEAR)"
	@$(AR) $(NAME) $@

clean :
	@echo "$(RED)Cleaning $(OBJ_DIR)...$(RESET)"
	@${RM} obj

fclean : clean
	@echo "$(RED)Cleaning $(NAME)...$(RESET)"
	@${RM} $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
