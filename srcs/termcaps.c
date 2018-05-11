/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:16:11 by amordret          #+#    #+#             */
/*   Updated: 2018/05/11 18:13:36 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

void    termcaps_echo(char c)
{
    if (c == 0)
        (g_termcaps.current_termios).c_lflag &= ~(ECHO);
    else
        (g_termcaps.current_termios).c_lflag &= (ECHO);
     if (tcsetattr(0, TCSANOW, &(g_termcaps.current_termios)) < 0)
        return (ft_putstr(ERR_TCSETATTR));
}

void    termcaps_echoandputchar(char c)
{
    termcaps_echo(1);
    ft_putchar(c);
    termcaps_echo(0);
}

void    termcaps_strings(void)
{
    if ((g_termcaps.cursordown = tgetstr("do", NULL)) == NULL)
        ft_putstr(ERR_TGETSTR);
    if ((g_termcaps.cursorup = tgetstr("up", NULL)) == NULL)
        ft_putstr(ERR_TGETSTR);
    if ((g_termcaps.cursorright = tgetstr("nd", NULL)) == NULL)
        ft_putstr(ERR_TGETSTR);
    if ((g_termcaps.cursorleft = tgetstr("le", NULL)) == NULL)
        ft_putstr(ERR_TGETSTR);
}

void    ft_set_term(void)
{
    char    *terminame;

    if ((terminame = getenv("TERM"))== NULL)
        return (ft_putstr(ERR_GETENV));
    if ((tgetent(NULL, terminame)) < 1)
        return (ft_putstr(ERR_TGETENT));
    if ((tcgetattr(0, &(g_termcaps.current_termios)) == -1) ||
	(tcgetattr(0, &(g_termcaps.backup_termios)) == -1))
        return (ft_putstr(ERR_TCGETATTR));
    (g_termcaps.current_termios).c_lflag &= ~(ICANON);
	(g_termcaps.current_termios).c_lflag &= ~(ECHO);
	(g_termcaps.current_termios).c_cc[VMIN] = 1;
	(g_termcaps.current_termios).c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &(g_termcaps.current_termios)) < 0)
        return (ft_putstr(ERR_TCSETATTR));
    termcaps_strings();
}
