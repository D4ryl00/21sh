/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_termcaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 16:51:27 by amordret          #+#    #+#             */
/*   Updated: 2018/05/14 14:50:17 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void input_is_left(int *cursorpos)
{
    ft_putstr_fd(g_termcaps.cursorleft, 0);
        if (*cursorpos == 0)
            return ;
        (*cursorpos)--;
}

void    input_is_special_char(char c[4], int *cursorpos)
{
    if (c[0] == 3)
        exit(0);
    if (c[0] == 27 && c[1] == 91 && c[2] == 68)
        return (input_is_left(cursorpos));
    /*if (c[0] == 27 && c[1] == 91 && c[2] == 67)
        return (input_is_right(cursorpos));
    if (c[0] == 27 && c[1] == 91 && c[2] == 65)
        return (input_is_up(cursorpos));
    if (c[0] == 27 && c[1] == 91 && c[2] == 65)
        return (input_is_down(cursorpos));
    if (c[0] == 127 && c[1] == 91 && c[2] == 66)
        return (input_is_backspace(cursorpos));
    if (c[0] == 27 && c[1] == 91 && c[2] == 51)
        return (input_is_del(cursorpos));
    ft_putnbr(c[0]);
    ft_putchar(' ');
    ft_putnbr(c[1]);
    ft_putchar(' ');    
    ft_putnbr(c[2]);*/
}
