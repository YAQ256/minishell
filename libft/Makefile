# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 12:15:03 by cyacoub-          #+#    #+#              #
#    Updated: 2023/09/02 08:33:31 by saazcon-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## EXECUTABLE ##
NAME = libft.a
## COMPILATION ##
CC = gcc
CFLAGS = -Wall -Werror  -Wextra
DEBUG = -g3 -fsanitize=address
#Chedk Leak memory
LEAK = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s
## VARIABLES ##
AR = @ar rc
RM = @rm -f
MAKE_NOPRINT = $(MAKE) --no-print-directory -C
## SOURCE FILE ##
SRC =	ft_atoi.c\
		ft_strncmp.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_strlen.c\
		ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_strnstr.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putnbr_fd.c\
		ft_putendl_fd.c\
		ft_strtrim.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_split.c\
		ft_lstseclast.c\
		ft_issign.c\
		ft_isspace.c\
		ft_swap.c\
		ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstsize.c\
		ft_lstadd_back.c\
		ft_lstlast.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c\
		ft_strcmp.c\
		ft_atoll.c\
		ft_memdel.c\

OBJS = ${SRC:.c=.o}
## COLORS ##
END     = \033[0m
RED     = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
BLUE    = \033[1;34m
WHITE   = \033[1;37m
## RULES ##
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Creating Libft $(END)"
	@$(AR) $(NAME) $(OBJS)
	@echo "$(GREEN)You Created $(NAME)$(END)"

## CLEANNING ##

clean:
	@$(RM) $(OBJS)

## REMOVING .O FILES AND .A FILES ##

fclean: clean
	$(RM) $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME): $(RED) → $(BLUE)was deleted$(END)"

## REMOVING AND RUNNING ##

re: fclean all

.PHONY: all re clean fclean 