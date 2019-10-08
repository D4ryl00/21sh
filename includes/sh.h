/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:34:06 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/08 11:46:35 by rbarbero         ###   ########.fr       */
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
# include <time.h>

# define VERSION "21sh"

# define PROMPT1		"\033[0;30;44m"
# define PROMPT2		"\033[0;33m $>"
# define PROMPT3		"\033[0m "

# define VIMMODEPROMPT1	"\033[0;30;107m"
# define VIMMODEPROMPT2 "VIM MODE ACTIVE"
# define VIMMODEPROMPT3 " \033[0;33m $>\033[0m "
# define VIMINSERTMODEPROMPT2 "-- VISUAL --"

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
	int							cursorposinline;
	int							cursorline;
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
	char						*deletetoend;
	char						*delete;
	char						*deleteline;
	char						*returnhome;
	char						*entervideomode;
	char						*leavevideomode;
	int							writtenchars;
	int							fd;
	int							promptlength;
}								t_termcaps;

enum							e_errno
{
	ENOMEM,
	ENOCMD,
	ENOENT,
	ENOTDIR,
	EACCES,
	EBUFF,
	ESYNT,
	EFORK,
	EWAIT,
	EOPEN,
	EDUP,
	EPIPE,
	ENONUM,
	EOTHER
};

/*
** Globales
*/

extern char						*g_errors[];
extern t_command_history		*g_first_cmd_history;
extern t_list					*g_env;
extern t_termcaps				g_termcaps;
extern t_read_input				*g_s;

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
int								return_perror(enum e_errno num, char *str,
		int value);
int								return_print(char *str, int status);
void							ft_perror(enum e_errno num, char *str
		, int suffix);
void							prompt(char *promptstring);
enum e_token					token_get_op_type(char *str);
void							token_free(void *content, size_t size);
void							ft_set_term(void);
int								read_input(t_input *input, char *promptstring);
void							termcaps_echo(char c);
void							term_putchar(char c);
void							termcaps_reset_term(void);
void							term_putstr(char *s);
void							term_putstr_fd(char *s, int fd);
void							input_is_special_char(t_read_input *readstruct);
void							termcaps_reset_term_and_exit(int status);
void							input_is_backspace(int *cursorpos,
								t_buf *buffer, t_read_input *s);
void							input_is_del(int *cursorpos, t_buf *buffer);
void							input_is_ctrld(int *cursorpos, t_buf *buffer);
void							input_is_up(t_read_input *s);
void							input_is_down(t_read_input *s);
void							input_is_end(t_read_input *s);
void							input_is_right(int *cursorpos, t_read_input *s);
void							input_is_left(int *cursorpos, t_read_input *s);
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
int								get_real_windows_width(void);
void							add_to_command_hist(char *line);
void							save_current_hist(t_read_input *s);
void							append_line_to_prev_hist(char *line);
char							*p_to_equ_char(char *str);
int								env_select_key(t_list *node, void *data);
char							*env_get_value(char *str);
void							env_del_entry(void *content, size_t size);
int								is_valid_posix_name(char *str);
char							*get_env_value(char *str);
void							reprint_after(t_read_input *s);
void							go_vim_mode(t_read_input *s);
void							vimmode_reprint_all(t_read_input *s,
								int initialcursorpos);
void							vimmode_print_prompt(int initialcursorpos);
void							visualmode(t_read_input *s, char **yanked);
void							visualmode_reprint_all(t_read_input *s,
								int initialcursorpos, int cursorposbackup);
int								esc_was_pressed(t_read_input *s);
void							yank(int initialcursorpos, t_read_input *s,
								char **yanked);
void							startend(int initialcursorpos, int cursorpos,
								int *a, int *b);
void							vim_paste(t_read_input *s, char **yanked);
void							vim_free_yanked(char **yanked);
void							vimcut(int initialcursorpos,
								t_read_input *s, char **yanked);
void							highlight(t_read_input *s, int initialcursorpos,
								int cursorposbackup);
int								d_was_pressed_again(t_read_input *s);
void							sig_winch(int i);
#endif
