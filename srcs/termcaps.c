/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:16:11 by amordret          #+#    #+#             */
/*   Updated: 2018/05/16 12:55:31 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

void	termcaps_echo(char c)
{
	if (c == 0)
		(g_termcaps.current_termios).c_lflag &= ~(ECHO);
	else
		(g_termcaps.current_termios).c_lflag &= (ECHO);
	if (tcsetattr(0, TCSANOW, &(g_termcaps.current_termios)) < 0)
		return (ft_putstr(ERR_TCSETATTR));
}

void	termcaps_strings(void)
{
	if ((g_termcaps.cursordown = tgetstr("do", NULL)) == NULL)
		ft_putstr(ERR_TGETSTR);
	if ((g_termcaps.cursorup = tgetstr("up", NULL)) == NULL)
		ft_putstr(ERR_TGETSTR);
	if ((g_termcaps.cursorright = tgetstr("nd", NULL)) == NULL)
		ft_putstr(ERR_TGETSTR);
	if ((g_termcaps.cursorleft = tgetstr("le", NULL)) == NULL)
		ft_putstr(ERR_TGETSTR);
	if ((g_termcaps.enterinsertmode = tgetstr("im", NULL)) == NULL)
		ft_putstr(ERR_TGETSTR);
	if ((g_termcaps.leaveinsertmode = tgetstr("ei", NULL)) == NULL)
		ft_putstr(ERR_TGETSTR);
	if ((g_termcaps.delete = tgetstr("dc", NULL)) == NULL)
		ft_putstr(ERR_TGETSTR);
}

void	termcaps_reset_term_and_exit(void)
{
	if (tcsetattr(0, TCSANOW, &(g_termcaps.backup_termios)) < 0)
		return (ft_putstr(ERR_TCSETATTR));
	ft_putstr_fd(g_termcaps.leaveinsertmode, 0);
	exit(0);
}

void	ft_set_term(void)
{
	char	*terminame;

	if ((terminame = getenv("TERM")) == NULL)
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
	ft_putstr_fd(g_termcaps.enterinsertmode, 0);
}
