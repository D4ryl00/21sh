/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:16:11 by amordret          #+#    #+#             */
/*   Updated: 2018/05/09 13:18:10 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

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
	//(g_termcaps.current_termios).c_lflag &= ~(ECHO);
	(g_termcaps.current_termios).c_cc[VMIN] = 1;
	(g_termcaps.current_termios).c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &(g_termcaps.current_termios)) < 0)
        return (ft_putstr(ERR_TCSETATTR));
}
