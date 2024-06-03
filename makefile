# Standard
NAME				= minishell

# Directories
LIBFT				= ./libft/libft.a
INC					= inc/
SRC_DIR				= srcs/
OBJ_DIR				= obj/

# Compiler and CFlags
CC					= gcc
CFLAGS				= -Wall -Werror -Wextra -I
RM					= rm -f
READLINE			= -lreadline

# Source Files
MINI_SHELL_DIR		=	$(SRC_DIR)

# Concatenate all source files
SRCS 				=   srcs/env.c\
						srcs/free.c\
						srcs/main.c \
						srcs/print_utils.c \
						srcs/signals.c\
						srcs/utils.c\
						srcs/parsing/check_lexer.c\
						srcs/parsing/lexer.c\
						srcs/parsing/token_management.c\
						srcs/parsing/tokenizer_one.c\
						srcs/parsing/tokenizer_two.c\
						srcs/parsing/tokenizer_three.c\
						srcs/parsing/tokenizer_utils.c\

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build rules
start:				
					@make all

$(LIBFT):
					@make -C ./libft

all: 				$(NAME)

$(NAME): 			$(OBJ) $(LIBFT)
					@$(CC) $(CFLAGS) $(INC) $(OBJ) $(READLINE) $(LIBFT) -o $(NAME)

# Compile object files from source files
$(OBJ_DIR)%.o:		$(SRC_DIR)%.c 
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
					@$(RM) -r $(OBJ_DIR)
					@make clean -C ./libft

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

re: fclean all

# Phony targets represent actions not files
.PHONY: 			start all clean fclean re
