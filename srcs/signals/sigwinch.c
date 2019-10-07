/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigwinch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 13:31:00 by amordret          #+#    #+#             */
/*   Updated: 2019/10/07 15:10:57 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void    sig_winch(int a)
{
    //t_read_input		sbis;
    struct sigaction	action;
	int					status;

    if (a == -1 || g_s == NULL)
    	return ;
	action.sa_handler = SIG_IGN;
	status = sigaction(SIGWINCH, &action, NULL);
    //return ;
    g_s->c[0] = 0;
    //Adri: when window is winched, reprint current
    //g_s->cursorpos = get_cursorpos(g_s->cursorpos);
    //input_is_home(&sbis);
    input_is_home(g_s);
	reprint_after(g_s);
    //while (sbis.cursorpos > 10)
    //{
     //   ft_putchar('\n');
       // input_is_del(&sbis.cursorpos, &sbis.buffer);
    //}
    action.sa_handler = &sig_winch;
	status = sigaction(SIGWINCH, &action, NULL);
    //prompt(g_s->promptstring);
    //while (++i < g_s->buffer.i - 2)
      //ft_putchar((g_s->buffer.buf)[i]);
    //input_is_backspace(&g_s->cursorpos, &g_s->buffer, g_s);
}