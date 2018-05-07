/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 09:11:23 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/25 10:21:35 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_buf_add_char(t_buf *buffer, char c)
{
	int	data_len;

	data_len = 1;
	if (buffer->i + data_len >= buffer->size)
	{
		if (!ft_buf_extend(buffer))
			return (0);
	}
	buffer->buf[(buffer->i)++] = c;
	return (1);
}
