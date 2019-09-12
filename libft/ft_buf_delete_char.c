/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf_delete_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:55:24 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/12 17:05:13 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_buf_delete_char(t_buf *buffer, int index)
{
	int	i;

	if (index >= buffer->i)
		return (-1);
	i = index - 1;
	while (++i < buffer->i - 1)
		buffer->buf[i] = buffer->buf[i + 1];
	buffer->buf[i] = '\0';
	(buffer->i)--;
	return (0);
}
