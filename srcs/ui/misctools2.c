/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misctools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:10:20 by amordret          #+#    #+#             */
/*   Updated: 2019/10/11 15:18:50 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		get_real_windows_width(void)
{
	struct winsize	ws;

	ioctl(g_termcaps.fd, TIOCGWINSZ, &ws);
	if (ws.ws_col == 0)
		return (1);
	return (ws.ws_col);
}

int		get_windows_width(void)
{
	struct winsize	ws;

	return (ioctl(g_termcaps.fd, TIOCGWINSZ, &ws));
}

void	term_putchar(char c)
{
	ft_putchar(c);
	g_termcaps.writtenchars++;
}

void	term_putstr(char *s)
{
	ft_putstr(s);
	g_termcaps.writtenchars += ft_strlen(s);
}

void	term_putstr_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	g_termcaps.writtenchars += ft_strlen(s);
}
