/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf_flush.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 10:50:46 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/25 10:19:15 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_buf_flush(t_buf *buffer)
{
	char	*tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * (buffer->i + 1))))
		return (NULL);
	ft_memcpy(tmp, buffer->buf, buffer->i);
	tmp[buffer->i] = '\0';
	buffer->i = 0;
	return (tmp);
}
