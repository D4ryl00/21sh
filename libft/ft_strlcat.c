/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:28:04 by rbarbero          #+#    #+#             */
/*   Updated: 2017/11/10 14:03:39 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	count_dst;
	size_t	count_src;
	size_t	rst;
	size_t	tmp;

	tmp = size;
	count_dst = 0;
	count_src = 0;
	while (tmp-- && *dst++)
		count_dst++;
	while (*src++)
		count_src++;
	dst--;
	src -= count_src + 1;
	rst = size - count_dst;
	if (rst == 0)
		return (count_dst + count_src);
	while (*src && rst != 1)
	{
		*dst++ = *src++;
		rst--;
	}
	*dst = '\0';
	return (count_dst + count_src);
}
