/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:34:06 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/15 18:25:28 by amordret         ###   ########.fr       */
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

# define BUF_SIZ		10
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
enum							e_type
{
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	NEWLINE,
	IO_NUMBER
};
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
	t_command_history			**first_command_hist;
	int							fd_history;

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
}								t_termcaps;

t_termcaps						g_termcaps;

typedef struct					s_token
{
	enum e_type					type;
	char						*content;
}								t_token;

enum							e_op_type
{
	AND_IF,
	O_RIF,
	DSEMI,
	DLESS,
	DGREAT,
	LESSAND,
	GREATAND,
	LESSGREAT,
	DLESSDASH,
	CLOBBER
};

typedef struct					s_op_token
{
	enum e_op_type				type;
	char						*content;
	void						*op;
}								t_op_token;

extern char						*g_op_token [];

enum							e_errno
{
	ENOMEM,
	enocmd,
	enoent,
	eacces,
	EOTHER
};

typedef struct					s_input
{
	char						*str;
	char						*save;
}								t_input;

extern char						*g_errors[];

int								newprompt(t_input *input, char *promptstring);
void							exit_perror(enum e_errno num, char *str);
int								return_perror(enum e_errno num, char *str);
void							prompt(char *promptstring);
t_btree							*eval(t_btree *ast, t_input *input);
t_list							*get_tokens(t_input *input);
void							token_free(void *content, size_t size);
void							ft_set_term(void);
int								read_input(t_input *input);
void							termcaps_echo(char c);
void							termcaps_echoandputchar(char c);
void							input_is_special_char(t_read_input *readstruct);
void							termcaps_reset_term_and_exit(void);

#endif
