# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amordret <amordret@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/04 17:30:48 by rbarbero          #+#    #+#              #
#    Updated: 2018/10/06 00:06:19 by rbarbero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

DIR_SRCS = srcs
SRCS_MAIN = main.c error.c free.c eval.c termcaps.c prompt.c input.c \
	   input_termcaps.c input_upanddown.c misctools.c history.c \
	   get_token_expansion.c get_token_arithmetic.c \
	   get_token_substitution.c get_token_word.c \
	   get_token_various.c classify_token.c history2.c \
	   env_tools.c history_file.c input_homeend.c

DIR_LEXER = $(DIR_SRCS)/lexer
SRCS_LEXER = lexer.c globals.c lexer_operator.c lexer_quote.c

DIR_PARSER = $(DIR_SRCS)/parser
SRCS_PARSER = cmd_name.c cmd_word.c filename.c io_file.c here_end.c io_here.c \
		   io_redirect.c cmd_suffix.c cmd_prefix.c simple_command.c \
		   command.c separator_op.c newline_list.c linebreak.c \
		   pipe_sequence.c pipeline.c and_or.c list.c complete_command.c \
		   complete_commands.c program.c

DIR_EVAL = $(DIR_SRCS)/eval
SRCS_EVAL = program.c pipeline.c pipe_sequence.c command.c simple_command.c \
			builtin_cmd.c special_builtin_cmd.c utility_cmd.c cmd_select.c \
			run.c redirection_core.c redirections.c

SRCS = $(addprefix $(DIR_SRCS)/,$(SRCS_MAIN)) \
	   $(addprefix $(DIR_LEXER)/, $(SRCS_LEXER)) \
	   $(addprefix $(DIR_PARSER)/, $(SRCS_PARSER)) \
	   $(addprefix $(DIR_EVAL)/, $(SRCS_EVAL))

OBJS = $(SRCS:%.c=%.o)

LIB_DIR = libft

HEADERS = sh.h lexer.h parser.h eval.h
HEADERS_DIR = includes/
LHEADERS = $(HEADERS:%.h=$(HEADERS_DIR)%.h)

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

$(OBJS): %.o: %.c $(LHEADERS)
	$(CC) $(CFLAGS) -I $(HEADERS_DIR) -I $(LIB_DIR)/includes -o $@ -c $<

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIB_DIR) $@

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIB_DIR) $@

re: fclean all
