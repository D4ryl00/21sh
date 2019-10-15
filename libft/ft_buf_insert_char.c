/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf_insert_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:39:01 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/15 16:42:51 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_buf_insert_char(t_buf *buffer, char c, int index)
{
	int	data_len;
	int	end;

	data_len = 1;
	if (index > buffer->i)
		return (-1);
	if (buffer->i + data_len >= buffer->size)
	{
		if (ft_buf_extend(buffer) == -1)
			return (-1);
	}
	end = buffer->size - 1;
	while (--end >= index)
		buffer->buf[end + 1] = buffer->buf[end];
	buffer->buf[index] = c;
	(buffer->i)++;
	return (0);
}
