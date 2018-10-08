/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:34:06 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/08 12:52:57 by amordret         ###   ########.fr       */
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

# define MAX_HISTORY	1000

typedef struct termios			t_termios;

typedef struct					s_command_history
{
	char						*command;
	struct s_command_history	*next;
}								t_command_history;

typedef struct					s_read_input
{
	char						c[4];
	char						*promptstring;
	char						*tmpline;
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
	int							fd;
	int							promptlength;
}								t_termcaps;


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
	NEWLINE,
	CONTROL
};

typedef struct					s_token
{
	enum e_token				type;
	char						*content;
}								t_token;

enum							e_errno
{
	ENOMEM,
	ENOCMD,
	ENOENT,
	EACCES,
	EBUFF,
	ESYNT,
	EFORK,
	EWAIT,
	EOPEN,
	EDUP,
	EPIPE,
	EOTHER
};

/*
** Globales
*/

extern char						*g_errors[];
extern t_command_history		*g_first_cmd_history;
extern t_list					*g_env;
extern t_termcaps				g_termcaps;
extern char						*g_op_token[];
extern char						*g_control_operator[];

typedef struct					s_input
{
	char						*str;
	char						*save;
}								t_input;

/*
** Prototypes
*/

int								newprompt(t_input *input, char *promptstring);
int								get_new_tokens(t_list **empty_tokens
		, t_list *start);
void							exit_perror(enum e_errno num, char *str);
int								return_perror(enum e_errno num, char *str);
void							ft_perror(enum e_errno num, char *str
		, int suffix);
void							prompt(char *promptstring);
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
void							insert_token(t_list **tokens, char *token
	, enum e_token type);
int								comment_input(t_input *input);
int								delimiter_case(t_list **tokens, t_buf *buffer
	, t_input *input, unsigned char f_params[2]);
enum e_token					token_get_op_type(char *str);
void							token_free(void *content, size_t size);
void							ft_set_term(void);
int								read_input(t_input *input, char *promptstring);
void							termcaps_echo(char c);
void							term_putchar(char c);
void							termcaps_reset_term(void);
void							term_putstr(char *s);
void							input_is_special_char(t_read_input *readstruct);
void							termcaps_reset_term_and_exit(void);
void							input_is_backspace(int *cursorpos,
	t_buf *buffer, t_read_input *s);
void							input_is_up(t_read_input *s);
void							input_is_down(t_read_input *s);
void							input_is_end(t_read_input *s);
void							input_is_right(int *cursorpos);
void							input_is_home(t_read_input *s);
void							input_is_nextorprevword(t_read_input *s);
void							input_is_nextword(t_read_input *s);
void							input_is_prevword(t_read_input *s);
int								open_history_file(char write);
void							close_history_file(int fd);
void							fill_command_hist(void);
void							save_hist_to_file(void);
int								max_history_reached(t_read_input *s);
void							free_minilibx(t_command_history *lasthistory);
int								termcaps_clearline(t_read_input *s);
int								termcaps_clearlineandbuff(t_read_input *s);
int								get_cursorpos(int cursorpos);
int								get_windows_width(void);
void							add_to_command_hist(char *line);
void							save_current_hist(t_read_input *s);
void							append_line_to_prev_hist(char *line);
char							*p_to_equ_char(char *str);
int								env_select_key(t_list *node, void *data);

# include "parser.h"
# include "eval.h"
#endif
