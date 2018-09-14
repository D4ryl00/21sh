/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:34:06 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/14 16:49:58 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "../libft/includes/libft.h"
# include <termios.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/ioctl.h>

# define PROMPT1		"\033[0;30;44m"
# define PROMPT2		"\033[0;33m $>"
# define PROMPT3		"\033[0m "

# define ERR_GETENV		"\nGETENV() error. Check ENV. TERMCAPS OFF\n"
# define ERR_TGETENT    "\nTGETENT() error. Check ENV. TERMCAPS OFF\n"
# define ERR_TCGETATTR  "\nTCGETATTR() error. Check ENV. TERMCAPS OFF\n"
# define ERR_TCSETATTR  "\nTCSETATTR() error. Check ENV. TERMCAPS OFF\n"
# define ERR_TGETSTR    "\nTGETSTR() error. Check ENV. cursor move wont work \n"
# define ERR_READ       "\nread() error. Check ~/.21sh. History wont work \n"
# define ERR_CLOSE		"\nclose() error :S. crap...\n"
# define ERR_COM_HIST	"\nError while fetching command history -> Wont work \n"

typedef struct termios			t_termios;

typedef struct					s_command_history
{
	char						*command;
	struct s_command_history	*next;
}								t_command_history;

typedef struct					s_read_input
{
	char						c[4];
	t_buf						buffer;
	int							cursorpos;
	int							charsinline;
	int							historynb;

}								t_read_input;

typedef struct					s_termcaps
{
	t_termios					current_termios;
	t_termios					backup_termios;
	char						*cursorup;
	char						*cursordown;
	char						*cursorleft;
	char						*cursorright;
	char						*enterinsertmode;
	char						*leaveinsertmode;
	char						*delete;
	char						*deleteline;
	char						*returnhome;
	int							writtenchars;
}								t_termcaps;

t_termcaps						g_termcaps;

/*
** The order of the first ten entries is important.
** It's linked with g_op_token.
** PLEASE DO NOT CHANGE THAT!
*/
enum							e_token
{
	AND_IF,
	OR_IF,
	DSEMI,
	DLESS,
	DGREAT,
	LESSAND,
	GREATAND,
	LESSGREAT,
	DLESSDASH,
	CLOBBER,
	TOKEN,
	IO_NUMBER,
	ASSIGNMENT_WORD,
	NAME,
	NEWLINE
};
typedef struct					s_token
{
	enum e_token				type;
	char						*content;
}								t_token;

extern char						*g_op_token[];

enum							e_errno
{
	ENOMEM,
	enocmd,
	enoent,
	eacces,
	EBUFF,
	EOTHER
};

typedef struct					s_input
{
	char						*str;
	char						*save;
}								t_input;

/*
** Structures for the AST
*/

typedef struct					s_ast_cmd_name
{
	char						*word;
}								t_ast_cmd_name;

typedef struct					s_ast_filename
{
	char						*word;
}								t_ast_filename;

typedef struct					s_ast_io_file
{
	char						*operator;
	t_ast_filename				*filename;
}								t_ast_io_file;

typedef struct					s_ast_here_end
{
	char						*word;
}								t_ast_here_end;

typedef struct					s_ast_io_here
{
	char						*operator;
	t_ast_here_end				*here_end;
}								t_ast_io_here;

typedef struct					s_ast_io_redirect
{
	char						ionumber[3];
	t_ast_io_file				*io_file;
	t_ast_io_here				*io_here;
}								t_ast_io_redirect;

typedef struct					s_ast_redirect_list
{
	t_list						*redirect_list;
	t_ast_io_redirect			*io_redirect;
}								t_ast_redirect_list;

typedef struct					s_ast_cmd_suffix
{
	t_ast_io_redirect			*io_redirect;
	char						*word;
	struct s_ast_cmd_suffix		*cmd_suffix;
}								t_ast_cmd_suffix;

typedef struct					s_ast_simple_command
{
	t_ast_cmd_name				*cmd_name;
	t_ast_cmd_suffix			*cmd_suffix;
}								t_ast_simple_command;

typedef struct					s_ast_command
{
	t_ast_simple_command		*simple_command;
	t_ast_redirect_list			*redirect_list;
}								t_ast_command;

typedef struct					s_ast_program
{
	t_ast_command				*command;
}								t_ast_program;

/*
** Globales
*/

extern char						*g_errors[];
extern t_command_history		*g_first_cmd_history;

/*
** Prototypes
*/

int								newprompt(t_input *input, char *promptstring);
void							exit_perror(enum e_errno num, char *str);
int								return_perror(enum e_errno num, char *str);
void							prompt(char *promptstring);
t_ast_program					*eval(t_input *input);
t_list							*get_tokens(t_input *input);
int								sq_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2]);
int								bs_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2]);
int								dq_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2]);
int								dollar_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2]);
int								get_token_expansion(t_buf *buffer
		, t_input *input, unsigned char f_params[2]);
int								get_token_arithmetic(t_buf *buffer
		, t_input *input, unsigned char f_params[2]);
int								substitution_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2], char close);
int								bq_input(t_buf *buffer, t_input *input
		, unsigned char f_params[2]);
int								word_add_char_case(t_buf *buffer
		, t_input *input);
int								word_start_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2]);
int								 is_operator(t_buf *buffer, char c
		, unsigned char f_params[2]);
int								operator_case(t_list **tokens, t_buf *buffer
		, t_input *input, unsigned char f_params[2]);
int								operator_start_case(t_list **tokens
		, t_buf *buffer, t_input *input, unsigned char f_params[2]);
int								insert_token(t_list **tokens, char *token);
int								comment_input(t_input *input);
int								delimiter_case(t_list **tokens, t_buf *buffer
		, t_input *input, unsigned char f_params[2]);
void							token_free(void *content, size_t size);
void							ft_set_term(void);
int								read_input(t_input *input);
void							termcaps_echo(char c);
void							termcaps_echoandputchar(char c);
void							termcaps_echoandputstr(char *s);
void							input_is_special_char(t_read_input *readstruct);
void							termcaps_reset_term_and_exit(void);
void							input_is_backspace(int *cursorpos,
								t_buf *buffer);
void							input_is_up(t_read_input *s);
void							fill_command_hist(void);
int								termcaps_clearline(t_read_input *s);
int								termcaps_clearlineandbuff(t_read_input *s);
void							add_to_command_hist(char *line);
void							save_current_hist(t_read_input *s);
int								classify_token(t_list *tokens);
t_ast_program					*make_ast(t_list *tokens);
void							free_ast_program(t_ast_program *program);
void							free_ast_command(t_ast_command *command);
void							free_ast_simple_command(t_ast_simple_command *sc);
void							free_ast_cmd_suffix(t_ast_cmd_suffix *suffix);
void							free_ast_io_redirect(t_ast_io_redirect *redirect);
void							free_ast_io_file(t_ast_io_file *file);
#endif
