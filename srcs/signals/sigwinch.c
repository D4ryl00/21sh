/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigwinch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 13:31:00 by amordret          #+#    #+#             */
/*   Updated: 2019/10/01 15:52:13 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void    sig_winch(int a)
{
    int             i;
    t_read_input sbis;

    if (a == -1 || g_s == NULL)
        return ;
    i = -1;
    return ;
    sbis = *g_s;
    //Adri: when window is winched, reprint current
    g_s->cursorpos = get_cursorpos(g_s->cursorpos);
    //termcaps_clearline(&sbis);
    //term_putstr("hihihihihihi\n");
    //while (++i < g_s->buffer.i - 2)
     // ft_putchar((g_s->buffer.buf)[i]);
}