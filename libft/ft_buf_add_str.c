/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf_add_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 14:47:13 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/25 14:53:30 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_buf_add_str(t_buf *buffer, char *str)
{
	int	data_len;

	data_len = ft_strlen(str);
	if (buffer->i + data_len >= buffer->size)
	{
		if (ft_buf_extend(buffer) == -1)
			return (-1);
	}
	ft_strcpy(&(buffer->buf[buffer->i]), str);
	buffer->i += data_len;
	return (0);
}
