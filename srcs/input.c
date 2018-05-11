/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:31:31 by amordret          #+#    #+#             */
/*   Updated: 2018/05/11 17:00:35 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int     read_input(t_input *input)
{
    int     charsread;
    char    c;
    t_buf   buffer;

    charsread = 1;
    c = 'a';
    if (ft_buf_init(&buffer) == 0)
        return (-1);
    while (charsread && c != '\n')
    {
        charsread = read(0, &c, 1);
        if (ft_isprint(c) == 1 && (ft_buf_add_char(&buffer, c)) == 0)
            return (-1);
        if (ft_isprint(c) == 1 || c == '\n')
            termcaps_echoandputchar(c);
        else
            input_is_special_char(c);
    }
    if (ft_buf_add_char(&buffer, '\0') == 0 ||
    !((input->str) = ft_buf_flush(&buffer)))
        return (-1);
    input->save = &(input->str[0]);
    ft_buf_destroy(&buffer);
    return (charsread);
}