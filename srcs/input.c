/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:31:31 by amordret          #+#    #+#             */
/*   Updated: 2018/05/09 14:02:44 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int     read_input(t_input *input)
{
    int     charsread;
    char    c;
    t_buf   buffer;

    charsread = 1;
    if (ft_buf_init(&buffer) == 0)
        return (-1);
    while (charsread)
    {
        charsread = read(0, &c, 1);
        ft_buf_add_char(&buffer, c);
        if (c == '\n')
            break;
    }
    if (ft_buf_add_char(&buffer, '\0') == 0)
        return (-1);
    if (((t_input->str) = ft_strdup(buffer.buf)) == NULL)
        return (-1);
    t_input->save = &(t_input->str[0]);
    ft_buf_destroy(&buffer);
    return (charsread);
}