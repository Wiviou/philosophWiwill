
### Colors ###
TURQUOISE  = \033[0;36m
BLUE_ROYAL = \033[0;34m
BEIGE      = \033[38;5;223m
BOLD       = \033[1m
RESET      = \033[0m
ITALIC     = \033[3m

### Project ###
NAME      = philo
SRC_PATH  = src/
OBJ_DIR   = obj/
SRC       = $(SRC_PATH)main.c \
            $(SRC_PATH)error.c \
			$(SRC_PATH)error_2.c \
            $(SRC_PATH)ft_atol.c \
            $(SRC_PATH)set_param.c \
            $(SRC_PATH)philosophers.c \
            $(SRC_PATH)util.c \
			$(SRC_PATH)print.c \
			$(SRC_PATH)clear.c \
			$(SRC_PATH)put_up_or_down_fork.c \
			$(SRC_PATH)monitor.c \
			$(SRC_PATH)monitor2.c \
            $(SRC_PATH)action.c
OBJ       = $(addprefix $(OBJ_DIR), $(notdir $(SRC:.c=.o)))

### Compiler ###
CC       = cc
CFLAGS   = -Wall -Wextra -Werror -g3 -fsanitize=thread
RM       = rm -f

### Rules ###
all:    $(NAME)

$(OBJ_DIR)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(TURQUOISE)$(BOLD)$(ITALIC)-> Compiling $(BLUE_ROYAL)$(BOLD)[PHILO Files] => $(RESET)""$(BLUE_ROYAL) <$<> \033[K\r$(RESET)"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^
	@printf "\n\t$(BEIGE)$(BOLD)$(ITALIC)PHILO files compiled$(RESET) ✨\n\n"
	@printf "$(BOLD)$(ITALIC)$(TURQUOISE)🎉 PHILO COMPILED$(RESET) ✅\n\n"

clean:
	@$(RM) $(OBJ)
	@printf "\n\t$(TURQUOISE)$(BOLD)$(ITALIC)🧹 PHILO object files removed$(RESET) 🗂  ❌\n\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "\n\t$(TURQUOISE)$(BOLD)$(ITALIC)🧹 PHILO binary removed$(RESET) 💽 ❌\n\n"

re: fclean all

.PHONY: all clean fclean re
