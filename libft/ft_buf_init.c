/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 09:27:32 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/14 16:34:33 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_buf_init(t_buf *buffer)
{
	if (!(buffer->buf = (char *)ft_memalloc(sizeof(char) * BUFFER_SIZE)))
		return (-1);
	buffer->i = 0;
	buffer->size = BUFFER_SIZE;
	return (0);
}
