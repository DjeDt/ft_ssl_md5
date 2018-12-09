#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/26 16:31:33 by ddinaut           #+#    #+#              #
#    Updated: 2018/12/09 16:16:50 by ddinaut          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# Output file #
NAME	= ft_ssl

# Details #
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
ADDFLAGS	= #-fsanitize=address

# Directories
OBJ_DIR		= .obj
SRC_DIR		= srcs
INC_DIR		= includes/
LIB_PATH	= libft
PRINTF_PATH	= ft_printf


LIBFT		= -L $(LIB_PATH)
PRINTF		= -L $(PRINTF_PATH)
LIBS		= $(LIBFT) -lft $(PRINTF) -lftprintf
INCLUDES	= -I $(LIB_PATH)/$(INC_DIR) -I $(INC_DIR) -I $(PRINTF_PATH)/$(INC_DIR)

# Colors #
COL_BLACK	= \033[1;30m
COL_RED		= \033[1;31m
COL_GREEN	= \033[1;32m
COL_YELLOW	= \033[1;33m
COL_BLUE	= \033[1;34m
COL_PURPLE	= \033[1;35m
COL_WHITE	= \033[1;37m
CLEAN_LINE	= \033[K
END_COL		= \033[0;m

# Sources #
SRCS =						\
	ft_ssl.c				\
	manage_md5.c			\
	routine_md5.c			\
	algo_md5.c				\
	secure_hash_algo_512.c


OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
SRC_FILES = $(addprefix $(SRC_DIR)/,$(SRCS))

# Rules #
.PHONY: all clean fclean re libft ft_printf

all: $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) -o $@ $(FLAGS) $(ADDFLAGS) $(INCLUDES) -c $<


$(NAME): libft ft_printf $(OBJ_FILES)
	make -sC $(LIB_PATH)
	make -sC $(PRINTF_PATH)
	$(CC) -o $(NAME) $(FLAGS) $(ADDFLAGS) $(OBJ_FILES) $(LIBS)

libft:
	@printf "[Compiling libft] :\n"
	make -C libft/

ft_printf:
	@printf "\n[Compiling ft_printf] :\n"
	make -C ft_printf/

clean:
	/bin/rm -f $(OBJ_FILES)
#	make -C libft/ clean
#	make -C ft_printf/ clean

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(SMB_LINK)
#	make -C libft/ fclean
#	make -C ft_printf/ fclean

re: fclean all
