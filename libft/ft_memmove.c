/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:36:31 by rbarbero          #+#    #+#             */
/*   Updated: 2017/11/10 14:28:34 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*str_dst;
	char	*str_src;
	size_t	i;
	size_t	offset;

	if (dst > src)
	{
		str_dst = (char *)dst;
		str_src = (char *)src;
		i = -1;
		offset = len - 1;
		while (++i < len)
			str_dst[offset - i] = str_src[offset - i];
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
