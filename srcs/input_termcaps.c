/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_termcaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 16:51:27 by amordret          #+#    #+#             */
/*   Updated: 2018/05/11 18:14:01 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void    input_is_special_char(char c[4])
{
    if (c[0] == 3)
        exit(0);
    if (c[0] == 27 && c[1] == 91 && c[2] == 68)
        ft_putstr_fd(g_termcaps.cursorleft, 0);
   /* ft_putnbr(c[0]);
    ft_putchar(' ');
    ft_putnbr(c[1]);
    ft_putchar(' ');    
    ft_putnbr(c[2]);*/
}
