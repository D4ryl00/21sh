/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:31:31 by amordret          #+#    #+#             */
/*   Updated: 2018/05/11 18:05:24 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int     read_input(t_input *input)
{
    char    c[4];
    t_buf   buffer;

    c[0] = 0;
    c[3] = 1;
    if (ft_buf_init(&buffer) == 0)
        return (-1);
    while (c[3] && c[0] != '\n')
    {
        c[3] = read(0, &c, 3);
        if (ft_isprint(c[0]) == 1 && (ft_buf_add_char(&buffer, c[0])) == 0)
            return (-1);
        if (ft_isprint(c[0]) == 1 || c[0] == '\n')
            termcaps_echoandputchar(c[0]);
        else
            input_is_special_char(c);
    }
    if (ft_buf_add_char(&buffer, '\0') == 0 ||
    !((input->str) = ft_buf_flush(&buffer)))
        return (-1);
    input->save = &(input->str[0]);
    ft_buf_destroy(&buffer);
    return (c[3]);
}