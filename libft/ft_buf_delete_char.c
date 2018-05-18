/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf_delete_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:55:24 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/18 10:26:32 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_buf_delete_char(t_buf *buffer, int index)
{
	int	data_len;
	int	i;

	data_len = 1;
	if (index >= buffer->i)
		return (-1);
	i = index - 1;
	while (++i < buffer->i - 1)
		buffer->buf[i] = buffer->buf[i + 1];
	(buffer->i)--;
	return (0);
}
