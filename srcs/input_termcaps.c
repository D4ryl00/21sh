/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_termcaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 16:51:27 by amordret          #+#    #+#             */
/*   Updated: 2018/05/14 15:54:47 by amordret         ###   ########.fr       */
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

static void input_is_right(int *cursorpos, int bufferpos)
{
        if (*cursorpos == bufferpos)
            return ;
        ft_putstr_fd(g_termcaps.cursorright, 0);
        (*cursorpos)++;
}

static void input_is_del(int *cursorpos, int bufferpos)
{
        if (*cursorpos == bufferpos)
            return ;
        termcaps_echo(1);
        ft_putstr_fd(g_termcaps.delete, 0);
        ft_putstr_fd(g_termcaps.delete, 0);        
        termcaps_echo(0);
}

void    input_is_special_char(char c[4], int *cursorpos, int bufferpos,
char *czero)
{
    if (c[0] == 3)
        termcaps_reset_term_and_exit();
    if (c[0] == 27 && c[1] == 91 && c[2] == 68)
        return (input_is_left(cursorpos));
    if (c[0] == 27 && c[1] == 91 && c[2] == 67)
        return (input_is_right(cursorpos, bufferpos));
    if (c[0] == 27 && c[1] == 91 && c[2] == 51)
        return (input_is_del(cursorpos, bufferpos));
    /*if (c[0] == 27 && c[1] == 91 && c[2] == 65)
        return (input_is_up(cursorpos));
    if (c[0] == 27 && c[1] == 91 && c[2] == 65)
        return (input_is_down(cursorpos));
    if (c[0] == 127 && c[1] == 91 && c[2] == 66)
        return (input_is_backspace(cursorpos));
    ft_putnbr(c[0]);
    ft_putchar(' ');
    ft_putnbr(c[1]);
    ft_putchar(' ');    
    ft_putnbr(c[2]);*/
    *czero = 0;
}
