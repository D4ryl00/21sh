/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf_add_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:53:19 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/18 10:26:07 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_buf_add_char(t_buf *buffer, char c)
{
	int	data_len;

	data_len = 1;
	if (buffer->i + data_len >= buffer->size)
	{
		if (ft_buf_extend(buffer) == -1)
			return (-1);
	}
	buffer->buf[(buffer->i)++] = c;
	return (0);
}
