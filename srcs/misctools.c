/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misctools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:15:42 by amordret          #+#    #+#             */
/*   Updated: 2018/09/18 15:47:32 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free_minilibx(t_command_history *lasthistory)
{
	t_command_history	*next_element;

	if (lasthistory && lasthistory->command)
		while (lasthistory)
		{
			next_element = lasthistory->next;
			lasthistory->next = NULL;
			free(lasthistory->command);
			free(lasthistory);
			lasthistory = next_element;
		}
}

void	term_putchar(char c)
{
	termcaps_echo(1);
	ft_putchar(c);
	g_termcaps.writtenchars++;
	termcaps_echo(0);
}

void	term_putstr(char *s)
{
	termcaps_echo(1);
	ft_putstr(s);
	g_termcaps.writtenchars += ft_strlen(s);
	termcaps_echo(0);
}

int		termcaps_clearlineandbuff(t_read_input *s)
{
	ft_putstr_fd(g_termcaps.returnhome, 0);
	ft_putstr_fd(g_termcaps.deleteline, 0);
	if (s && s->cursorpos)
		s->cursorpos = 0;
	ft_buf_destroy(&(s->buffer));
	if (ft_buf_init(&(s->buffer)) == -1)
		return (-1);
	prompt(NULL);
	return (0);
}

int		termcaps_clearline(t_read_input *s)
{
	ft_putstr_fd(g_termcaps.returnhome, 0);
	ft_putstr_fd(g_termcaps.deleteline, 0);
	if (s && s->cursorpos)
		s->cursorpos = 0;
	prompt(NULL);
	return (0);
}
