# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amordret <amordret@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/04 17:30:48 by rbarbero          #+#    #+#              #
#    Updated: 2019/10/10 16:25:49 by rbarbero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

DIR_SRCS = srcs
SRCS_MAIN = main.c error.c free.c eval.c termcaps.c prompt.c input.c \
	   input_termcaps.c input_upanddown.c misctools.c history.c \
	   history2.c env_tools.c history_file.c input_homeend.c input_rightleft.c \
	   input_ctrl.c

DIR_LEXER = $(DIR_SRCS)/lexer
SRCS_LEXER = lexer.c globals.c lexer_operator.c lexer_quote.c \
			 lexer_expansion.c lexer_arithmetic.c lexer_substitution.c \
			 lexer_misc.c

DIR_PARSER = $(DIR_SRCS)/parser
SRCS_PARSER = cmd_name.c cmd_word.c filename.c io_file.c here_end.c io_here.c \
		   io_redirect.c cmd_suffix.c cmd_prefix.c simple_command.c \
		   command.c separator_op.c newline_list.c linebreak.c \
		   pipe_sequence.c pipeline.c and_or.c list.c complete_command.c \
		   complete_commands.c program.c compound_command.c subshell.c \
		   compound_list.c term.c separator.c

DIR_EVAL = $(DIR_SRCS)/eval
SRCS_EVAL = program.c pipeline.c pipe_sequence.c command.c simple_command.c \
			builtin_cmd.c special_builtin_cmd.c utility_cmd.c cmd_select.c \
			run.c redirections_core.c redirections.c redirections_undo.c \
			heredocs.c compound_command.c subshell.c complete_commands.c \
			complete_command.c list.c and_or.c pipe_sequence_misc.c

DIR_UTILITES = $(DIR_SRCS)/utilities
SRCS_UTILITES = cd.c cd_hyphen.c cd_setpwd.c cd_path_to_canonical.c \
				cd_select_path.c cd_stage1_misc.c cd_dot_dot.c fg.c bg.c \
				fg_bg_misc.c jobs.c

DIR_BUILTINS = $(DIR_SRCS)/builtins
SRCS_BUILTINS = echo.c env.c setenv.c unsetenv.c exit.c

DIR_JOBCONTROL = $(DIR_SRCS)/jobcontrol
SRCS_JOBCONTROL = init.c newjob.c waitjobs.c stop_job.c job_list_misc.c \
				  print_job_infos.c process_list_misc.c update_status.c

DIR_SIGNALS = $(DIR_SRCS)/signals
SRCS_SIGNALS = init.c sigwinch.c

DIR_VIM = $(DIR_SRCS)/vim
SRCS_VIM = vimmode.c visualmode.c vimmisctools.c vimmisctools2.c vimmode2.c \
			visualmode2.c

SRCS = $(addprefix $(DIR_SRCS)/,$(SRCS_MAIN)) \
	   $(addprefix $(DIR_LEXER)/, $(SRCS_LEXER)) \
	   $(addprefix $(DIR_PARSER)/, $(SRCS_PARSER)) \
	   $(addprefix $(DIR_EVAL)/, $(SRCS_EVAL)) \
	   $(addprefix $(DIR_UTILITES)/, $(SRCS_UTILITES)) \
	   $(addprefix $(DIR_BUILTINS)/, $(SRCS_BUILTINS)) \
	   $(addprefix $(DIR_JOBCONTROL)/, $(SRCS_JOBCONTROL)) \
	   $(addprefix $(DIR_SIGNALS)/, $(SRCS_SIGNALS)) \
	   $(addprefix $(DIR_VIM)/, $(SRCS_VIM))

OBJS = $(SRCS:%.c=%.o)

LIB_DIR = libft

HEADERS = sh.h lexer.h parser.h eval.h utilities.h builtins.h jobcontrol.h \
		  signals.h
HEADERS_DIR = includes/
LHEADERS = $(HEADERS:%.h=$(HEADERS_DIR)%.h)

CC = gcc
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
