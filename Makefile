# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amordret <amordret@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/04 17:30:48 by rbarbero          #+#    #+#              #
#    Updated: 2018/10/01 15:12:26 by rbarbero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRCS = main.c error.c free.c eval.c tokens.c termcaps.c prompt.c input.c \
	   input_termcaps.c input_upanddown.c misctools.c history.c \
	   get_token_quote.c get_token_expansion.c get_token_arithmetic.c \
	   get_token_substitution.c get_token_word.c get_token_operator.c \
	   get_token_various.c classify_token.c ast_make.c ast_free.c ast_eval.c \
	   env_tools.c run.c run_path.c history_file.c input_homeend.c \
	   ast_cmd_tools.c history2.c
SRCS_DIR = srcs/
LIB_DIR = libft

HEADERS = sh.h
HEADERS_DIR = includes/
LHEADERS = $(HEADERS:%.h=$(HEADERS_DIR)%.h)

OBJS = $(SRCS:%.c=%.o)

CC = clang
CFLAGS = -Wall -Wextra -Werror -Fsanitize=address

all: $(NAME)

debug: CFLAGS += -g
debug: all

$(NAME): $(OBJS) $(LIB_DIR)/libft.a
	$(CC) -lncurses -o $(NAME) $^
	clear
	echo "\033[1;31;43m"  "\n!!! \n!!!!!! \n!!!!!!!!! \n!!!!!!!!!!!!" ATRCHTUNG FLAG FSANITIZE A ENLEVER "\n\n\n\n" "\033[0m"

$(LIB_DIR)/libft.a:
	$(MAKE) -C $(LIB_DIR)

$(OBJS): %.o: $(SRCS_DIR)%.c $(LHEADERS)
	$(CC) $(CFLAGS) -I $(HEADERS_DIR) -I $(LIB_DIR)/includes -o $@ -c $<

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIB_DIR) $@

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIB_DIR) $@

re: fclean all
