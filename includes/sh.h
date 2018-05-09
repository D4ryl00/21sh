/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:34:06 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/09 13:48:04 by amordret         ###   ########.fr       */
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

# define BUF_SIZ        10
# define PROMPT1        "\033[0;30;44m"
# define PROMPT2        "\033[0;33m $>"
# define PROMPT3        "\033[0m "


# define ERR_GETENV		"GETENV() error. Check ENV. TERMCAPS OFF\n"
# define ERR_TGETENT    "TGETENT() error. Check ENV. TERMCAPS OFF\n"
# define ERR_TCGETATTR  "TCGETATTR() error. Check ENV. TERMCAPS OFF\n"
# define ERR_TCSETATTR  "TCSETATTR() error. Check ENV. TERMCAPS OFF\n"



enum                    e_type
{
    WORD,
    ASSIGNMENT_WORD,
    NAME,
    NEWLINE,
    IO_NUMBER
};
typedef struct termios  t_termios;

typedef struct          s_termcaps
{
    t_termios           current_termios;
    t_termios           backup_termios;
}                       t_termcaps;

t_termcaps               g_termcaps;

typedef struct          s_token
{
    enum e_type         type;
    char                *content;
}                       t_token;

enum                    e_op_type
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

typedef struct          s_op_token
{
    enum e_op_type      type;
    char                *content;
    void                *op;
}                       t_op_token;

extern char             *g_op_token [];

enum                    e_errno
{
    ENOMEM,
    enocmd,
    enoent,
    eacces,
    EOTHER
};

typedef struct          s_input
{
    char                *str;
    char                *save;
}                       t_input;

extern char             *g_errors[];

void                    exit_perror(enum e_errno num, char *str);
int                     return_perror(enum e_errno num, char *str);
int                     prompt(char *promptstring);
t_btree                 *eval(t_btree *ast, t_input *input);
t_list                  *get_tokens(t_input *input);
void                    token_free(void *content, size_t size);
void                    ft_set_term(void);
int                     read_input(t_input *input);

#endif
