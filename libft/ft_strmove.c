/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:36:31 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/15 17:03:24 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void		*ft_strmove(char *dst, const char *src)
{
	char		*str_dst;
	const char	*str_src;
	size_t		i;
	size_t		len;

	if (dst && src)
	{
		if (dst > src)
		{
			str_dst = dst;
			str_src = src;
			i = -1;
			len = ft_strlen(src);
			while (++i <= len)
				str_dst[len - i] = str_src[len - i];
		}
		else
			ft_strcpy(dst, src);
	}
	return (dst);
}
