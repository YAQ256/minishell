# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/07 11:51:51 by cyacoub-          #+#    #+#              #
#    Updated: 2023/09/06 08:45:59 by cyacoub-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## EXECUTABLE ##
NAME = minishell
## COMPILATION ##
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
READLINE_LIB= -L $(shell brew --prefix readline)/lib/ -lreadline -L . -lft
READLINE_HEADER= -I . -I$(shell brew --prefix readline)/include/ -I include/
## INCLUDE ##
LIBFT = ./libft/libft.a
#SRC_PATH = ./src/
#SRC_PATH_BONUS = ./bonus/
## VARIABLES ##
AR = @ar rcs
RM = @rm -f
LINK = -L $(LIBS_PATH)
## SOURCE FILE ##
SRCS =	builtins/echo.c builtins/env.c builtins/exit.c builtins/pwd.c \
		builtins/unset.c parsing/env_utils.c parsing/errors.c parsing/errors2.c\
		parsing/free.c parsing/get_cmd.c parsing/get_env.c parsing/path.c \
		parsing/str_check.c parsing/token.c parsing/token2.c \
		parsing/trim_vars.c minishell.c signals.c builtins/cd.c \
		exec/exec.c exec/utils.c exec/redir.c exec/break.c \
		builtins/builtin.c builtins/export/export.c \
		builtins/export/export_utils.c builtins/export/export_utils2.c \
		exec/utils2.c exec/heredoc.c parsing/exit_status_errors.c parsing/shlvl.c

SRC_BONUS =	
#SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJS = ${SRCS:.c=.o}

SRCS_BONUS = $(addprefix $(SRC_PATH_BONUS), $(SRC_BONUS))
OBJS_BONUS = ${SRCS_BONUS:.c=.o}
## COLORS ##
END     = \033[0m
RED     = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
BLUE    = \033[1;34m
WHITE   = \033[1;37m
## RULES ##
all: make_libft $(NAME)

make_libft:
	@echo "$(BLUE)Generating...$(RESET)"
	@make -sC ./libft
	@echo "$(NAME): $(GREEN)Done!$(RESET)"

%.o :%.c 
	@echo "${BLUE} ◎ $(YELLOW)Compiling   ${RED}→   $(WHITE)$< $(END)" 
	@$(CC) $(CFLAGS) $(READLINE_HEADER) -c -o $@ $< 

$(NAME) : make_libft $(OBJS)
	@make -sC ./libft
	@cp ./libft/libft.a ./
#	clear
	@$(CC) $(CFLAGS) $(READLINE_LIB) $(READLINE_HEADER) $(OBJS) $(LIBFT) -o $(NAME) -lreadline 
	@echo "$(GREEN)You Created $(NAME)$(END)"

#$(NAME2) : $(OBJS_BONUS)
#	clear
#	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o checker
#	@echo "$(GREEN)You Created Checker$(END)"

## CLEANNING ##

clean:
	@$(RM) $(OBJS)
	@cd ./libft && make clean 
	@echo "$(GREEN)$(NAME): $(RED)→ $(BLUE) Cleaning... $(END)"
	@echo "$(GREEN)$(NAME): $(RED)→ $(YELLOW) the files(*.o) were deleted $(END)"

## REMOVING .O FILES AND .A FILES ##

fclean: clean
	$(RM) $(NAME) $(OBJS) $(OBJS_BONUS)
	@make fclean -sC ./libft
	@$(RM) libft.a
	clear
	@echo "$(GREEN)$(NAME): $(RED) → $(BLUE)was deleted$(END)"

## REMOVING AND RUNNING ##

re: fclean all

.PHONY: all re clean fclean 