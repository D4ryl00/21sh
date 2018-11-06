/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf_add_nstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 15:41:57 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/04 15:46:05 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_buf_add_nstr(t_buf *buffer, char *str, int len)
{
	if (buffer->i + len >= buffer->size)
	{
		if (ft_buf_extend(buffer) == -1)
			return (-1);
	}
	ft_strncpy(&(buffer->buf[buffer->i]), str, len);
	buffer->i += len;
	return (0);
}
