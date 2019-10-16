/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vimmode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:59:04 by amordret          #+#    #+#             */
/*   Updated: 2019/10/16 15:55:24 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		vimmode_print_prompt(int initialcursorpos)
{
	int	i;

	i = -1;
	if (initialcursorpos < 0)
		return (prompt(NULL));
	term_putstr_fd(VIMMODEPROMPT1, 2);
	while ((++i + 9) < (g_termcaps.promptlength / 2))
		term_putchar(' ');
	term_putstr_fd(VIMMODEPROMPT2, 2);
	while ((++i + 19) < (g_termcaps.promptlength))
		term_putchar(' ');
	term_putstr_fd(VIMMODEPROMPT3, 2);
	g_termcaps.writtenchars = 0;
}

static void	vim_special_char(t_read_input *s)
{
	if (s->c[0] == 27 && esc_was_pressed(s))
	{
		s->c[0] = 22;
		return ;
	}
	if ((s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 68) || s->c[0] == 'h')
		return (input_is_left(&(s->cursorpos), s));
	if ((s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 67) || s->c[0] == 'l')
		return (input_is_right(&(s->cursorpos), s));
	if (s->c[0] == 'j')
		return (input_is_downline(s));
	if (s->c[0] == 'k')
		return (input_is_upline(s));
	if (s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 51)
		return (input_is_del(&(s->cursorpos), &(s->buffer)));
	if (s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 70)
		return (input_is_end(s));
	if (s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 72)
		return (input_is_home(s));
	if (s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 49)
		return (input_is_nextorprevword(s));
}

static char	*init_vim_mode(t_read_input *s, int *initialcursorpos)
{
	*initialcursorpos = s->cursorpos;
	s->c[0] = 0;
	s->c[1] = 0;
	s->c[2] = 0;
	s->c[3] = 1;
	vimmode_reprint_all(s, s->cursorpos);
	return (NULL);
}

static void	vimmode_d(t_read_input *s, char **yanked)
{
	if (d_was_pressed_again(s))
	{
		s->cursorpos = s->buffer.i;
		vimcut(0, s, yanked);
	}
}

void		go_vim_mode(t_read_input *s)
{
	int		initialcursorpos;
	char	**yanked;

	if ((yanked = malloc(sizeof(char*))) == NULL)
		exit_perror(ENOMEM, NULL);
	*yanked = init_vim_mode(s, &initialcursorpos);
	while (s->c[3] && s->c[0] != 22)
	{
		vimmode_reprint_all(s, initialcursorpos);
		s->c[3] = read(0, &(s->c), 1);
		if (s->c[0] == 127 || s->c[0] == 27 || s->c[0] == 3 || s->c[0] == 'h' ||
		s->c[0] == 'j' || s->c[0] == 'k' || s->c[0] == 'l')
			vim_special_char(s);
		if (s->c[0] == 'v' || s->c[0] == 'V')
			visualmode(s, yanked);
		if (s->c[0] == 'p' && *yanked)
			vim_paste(s, yanked);
		if (s->c[0] == 'd')
			vimmode_d(s, yanked);
	}
	vimmode_reprint_all(s, -1);
	vim_free_yanked(yanked);
}
