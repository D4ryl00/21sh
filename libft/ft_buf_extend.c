/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf_extend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 09:31:46 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/18 10:27:10 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_buf_extend(t_buf *buffer)
{
	char	*tmp;
	int		mult;
	long	new_size;

	mult = !(buffer->size % BUFFER_SIZE) ? buffer->size / BUFFER_SIZE :
		buffer->size / BUFFER_SIZE + 1;
	new_size = (mult + 1) * BUFFER_SIZE;
	if (!(tmp = (char *)malloc(sizeof(char) * new_size)))
		return (-1);
	buffer->size = new_size;
	ft_memcpy(tmp, buffer->buf, buffer->i);
	free(buffer->buf);
	buffer->buf = tmp;
	return (0);
}
