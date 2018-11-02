# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amordret <amordret@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/04 17:30:48 by rbarbero          #+#    #+#              #
#    Updated: 2018/11/02 10:34:58 by rbarbero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

DIR_SRCS = srcs
SRCS_MAIN = main.c error.c free.c eval.c termcaps.c prompt.c input.c \
	   input_termcaps.c input_upanddown.c misctools.c history.c \
	   history2.c env_tools.c history_file.c input_homeend.c

DIR_LEXER = $(DIR_SRCS)/lexer
SRCS_LEXER = lexer.c globals.c lexer_operator.c lexer_quote.c \
			 lexer_expansion.c lexer_arithmetic.c lexer_substitution.c \
			 lexer_misc.c

DIR_PARSER = $(DIR_SRCS)/parser
SRCS_PARSER = cmd_name.c cmd_word.c filename.c io_file.c here_end.c io_here.c \
		   io_redirect.c cmd_suffix.c cmd_prefix.c simple_command.c \
		   command.c separator_op.c newline_list.c linebreak.c \
		   pipe_sequence.c pipeline.c and_or.c list.c complete_command.c \
		   complete_commands.c program.c

DIR_EVAL = $(DIR_SRCS)/eval
SRCS_EVAL = program.c pipeline.c pipe_sequence.c command.c simple_command.c \
			builtin_cmd.c special_builtin_cmd.c utility_cmd.c cmd_select.c \
			run.c redirections_core.c redirections.c redirections_undo.c \
			heredocs.c

DIR_UTILITES = $(DIR_SRCS)/utilities
SRCS_UTILITES = cd.c

DIR_BUILTINS = $(DIR_SRCS)/builtins
SRCS_BUILTINS = echo.c env.c setenv.c unsetenv.c exit.c

SRCS = $(addprefix $(DIR_SRCS)/,$(SRCS_MAIN)) \
	   $(addprefix $(DIR_LEXER)/, $(SRCS_LEXER)) \
	   $(addprefix $(DIR_PARSER)/, $(SRCS_PARSER)) \
	   $(addprefix $(DIR_EVAL)/, $(SRCS_EVAL)) \
	   $(addprefix $(DIR_UTILITES)/, $(SRCS_UTILITES)) \
	   $(addprefix $(DIR_BUILTINS)/, $(SRCS_BUILTINS))

OBJS = $(SRCS:%.c=%.o)

LIB_DIR = libft

HEADERS = sh.h lexer.h parser.h eval.h utilities.h builtins.h
HEADERS_DIR = includes/
LHEADERS = $(HEADERS:%.h=$(HEADERS_DIR)%.h)

CC = clang
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

debug: CFLAGS += -g
debug: all

$(NAME): $(OBJS) $(LIB_DIR)/libft.a
	$(CC) -lncurses -o $(NAME) $^

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
